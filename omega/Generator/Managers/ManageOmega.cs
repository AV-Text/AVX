namespace Generator
{
    using System;
    using System.Collections.Generic;
    using System.Globalization;
    using System.IO;
    using System.Runtime.ExceptionServices;
    using System.Text;
    using System.Threading.Channels;
    using static System.Net.WebRequestMethods;

    public class ManageOmega
    {
        private TextWriter? bomOmega_MD5;
        private TextWriter? bomOmega;

        private BinaryReader? phoneticReader;
        private BinaryReader? sdkReader;
        private BinaryWriter? newWriter;
        private UInt64 version;
        private string SDK;

        public ManageOmega(string baseSDK, string newSDK)
        {
            this.bomOmega_MD5 = AVXManager.OpenTextWriter("AVX-Omega" + newSDK, ".md5");
            this.bomOmega = AVXManager.OpenTextWriter("AVX-Omega" + newSDK, ".txt");

            this.sdkReader = AVXManager.OpenBinaryReader("AVX-Omega" + baseSDK);
            var sdk = AVXManager.CreateSDK("AVX-Omega" + newSDK);
            this.newWriter = sdk.writer;
            this.SDK = sdk.path;

            this.phoneticReader = AVXManager.OpenBinaryReader("AV-Phonetics", ".binary");

            version = 0;
            for (int i = 1; i < newSDK.Length; i++)
            {
                int c = (int) (newSDK[i]);
                int digit = c - (int)'0';
                version *= 10;
                version += (byte) digit;
            }
        }
        public void CloseAllButMD5()
        {
            if (this.bomOmega != null)
                this.bomOmega.Close();

            if (this.sdkReader != null)
                this.sdkReader.Close();
            if (this.newWriter != null)
                this.newWriter.Close();

            if (this.phoneticReader != null)
                this.phoneticReader.Close();
        }
        public void CloseMD5()
        {
            if (this.bomOmega_MD5 != null)
                this.bomOmega_MD5.Close();
        }
        private static char[] whitespace = new char[] { ' ', '\t' };
        private void UpdatePhoneticsBOM()
        {
            if (this.phoneticReader != null)
            {
                this.phoneticReader.BaseStream.Seek(0, SeekOrigin.Begin);

                var label = "Phonetic".ToArray();
                var bom = BOM.Inventory[BOM.Phonetics];
                for (int i = 0; i < label.Length; i++)
                    bom.label[i] = (byte)label[i];
                for (int i = label.Length; i < bom.label.Length; i++)
                    bom.label[i] = (byte)0;
                bom.recordLength = 0;
                bom.recordCount = BOM.Inventory[BOM.OOV].recordCount + BOM.Inventory[BOM.Lexicon].recordCount - 1; // subtract 1 for zeroth-entry in lexicon
                bom.offset = (UInt32)(BOM.Inventory[(byte)(BOM.Phonetics - 1)].offset + BOM.Inventory[(byte)(BOM.Phonetics - 1)].length);
                UInt32 len = 0;

                for (int x = 1; x <= bom.recordCount; x++)
                {
                    var wkey = this.phoneticReader.ReadUInt16();
                    len += 2;

                    for (byte c = this.phoneticReader.ReadByte(); c != 0; c = this.phoneticReader.ReadByte())
                    {
                        len++;
                    }
                    len++;
                }
                bom.length = len;

                this.phoneticReader.BaseStream.Seek(0, SeekOrigin.Begin);
                bom.hash = this.CalculateMD5(this.phoneticReader.ReadBytes((int)len));
            }
        }
        private void WriteBinaryBOM(TOC bom)
        {
            if (this.newWriter != null)
            {
                this.newWriter.Write(bom.label);
                this.newWriter.Write(bom.offset);
                this.newWriter.Write(bom.length);
                this.newWriter.Write(bom.recordLength);
                this.newWriter.Write(bom.recordCount);
                this.newWriter.Write(bom.hash[0]);
                this.newWriter.Write(bom.hash[1]);
            }
        }
        private void WriteTextBOM(TOC bom)
        {
            if (this.bomOmega != null)
            {
                if (bom.label != null)
                {
                    int i = 0;
                    for (/**/; i < bom.label.Length; i++)
                        if (bom.label[i] != 0)
                            this.bomOmega.Write((char)bom.label[i]);
                        else
                            break;
                    for (/**/; i < 16; i++)
                        this.bomOmega.Write(' ');
                    this.bomOmega.Write("\t");
                }
                else
                {
                    for (int i = 0; i < 16; i++)
                        this.bomOmega.Write('-');
                    this.bomOmega.Write("\t");
                }
                this.bomOmega.Write(AVXManager.PadLeft(bom.offset.ToString(), 8)); this.bomOmega.Write("\t");
                this.bomOmega.Write(AVXManager.PadLeft(bom.length.ToString(), 8)); this.bomOmega.Write("\t");
                this.bomOmega.Write(AVXManager.PadLeft(bom.recordLength.ToString(), 8)); this.bomOmega.Write("\t");
                this.bomOmega.Write(AVXManager.PadLeft(bom.recordCount.ToString(), 8)); this.bomOmega.Write("\t");
                this.bomOmega.Write(bom.hash[0].ToString("X16") + bom.hash[1].ToString("X16"));
                this.bomOmega.Write("\n");
            }
        }
        private void WriteBOM(TOC bom)
        {
            WriteBinaryBOM(bom);
            WriteTextBOM(bom);
        }
        private void CreateDirectory()
        {
            if (this.sdkReader != null)
            {
                TOC bom;
                for (byte idx = 0; idx < BOM.Phonetics; idx++)
                {
                    bom = BOM.Inventory[idx];
                    bom.hash = new UInt64[2];

                    bom.label = this.sdkReader.ReadBytes(16);
                    bom.originalOffset = this.sdkReader.ReadUInt32();
                    bom.offset = 0;
                    bom.length = this.sdkReader.ReadUInt32();
                    bom.recordLength = this.sdkReader.ReadUInt32();
                    bom.recordCount = this.sdkReader.ReadUInt32();
                    bom.hash[0] = this.sdkReader.ReadUInt64();
                    bom.hash[1] = this.sdkReader.ReadUInt64();

                    if (idx == BOM.DIRECTORY)
                    {
                        bom.hash[0] = 0;
                        bom.hash[1] = this.version;
                        bom.recordCount = (UInt32)(BOM.Phonetics + 1);
                        bom.length = (UInt32)(bom.recordCount * bom.recordLength);
                    }
                    else
                    {
                        byte prev = (byte)(idx - 1);
                        bom.offset = (UInt32) (BOM.Inventory[prev].offset + BOM.Inventory[prev].length);
                    }
                    WriteBOM(bom);
                }
                this.UpdatePhoneticsBOM();
                bom = BOM.Inventory[BOM.Phonetics];
                WriteBOM(bom);
            }
        }
        private void CreateExistingArtifact(byte order)
        {
            if (this.sdkReader != null && this.newWriter != null)
            {
                var bom = BOM.Inventory[(byte)order];
                //this.sdkReader.BaseStream.Seek((int)bom.originalOffset, SeekOrigin.Begin);
                var bytes = this.sdkReader.ReadBytes((int)bom.length);

                this.newWriter.Write(bytes);
            }
        }
        private void CreateNewArtifact(byte order, BinaryReader? reader)
        {
            if (reader != null && this.newWriter != null)
            {
                var bom = BOM.Inventory[(byte)order];
                reader.BaseStream.Seek(0, SeekOrigin.Begin);
                var bytes = reader.ReadBytes((int)bom.length);

                this.newWriter.Write(bytes);
            }
        }
        public void Manage()
        {
            this.CreateDirectory();

            for (byte idx = 0; idx < BOM.Phonetics; idx++)
            {
                this.CreateExistingArtifact(idx);
            }
            this.CreateNewArtifact(BOM.Phonetics, this.phoneticReader);
            this.CloseAllButMD5();

            if (this.bomOmega_MD5 != null)
            {
                var bytes = System.IO.File.ReadAllBytes(this.SDK);
                var pair = CalculateMD5(bytes);

                this.bomOmega_MD5.Write(pair[0].ToString("X16") + pair[1].ToString("X16"));
            }
            this.CloseMD5();

        }
        private UInt64[] CalculateMD5(byte[] bytes)
        {
            UInt64[] result = new ulong[2] { 0, 0 };

            if (BOM.hasher != null)
            {
                var bval = BOM.hasher.ComputeHash(bytes);
                var sval = AVXManager.BytesToHex(bval);

                result[0] = UInt64.Parse(sval.Substring(0, 16), NumberStyles.HexNumber);
                result[1] = UInt64.Parse(sval.Substring(16), NumberStyles.HexNumber);
            }
            return result;
        }
        internal static string ReadByteString(BinaryReader breader, UInt16 maxLen = 24)
        {
            var buffer = new char[maxLen];

            int i = 0;
            byte c = 0;
            for (c = breader.ReadByte(); c != 0 && i < maxLen; c = breader.ReadByte())
                buffer[i++] = (char)c;
            buffer[i] = '\0';
            if (c != 0) for (c = breader.ReadByte(); c != 0; c = breader.ReadByte()) // discard ... this should not happen ... check in debugger
                    Console.WriteLine("Bad stuff!!!");

            return i > 0 ? new string(buffer, 0, i) : string.Empty;
        }
        internal static void WriteByteString(BinaryWriter bwriter, string token)
        {
            for (int i = 0; i < token.Length; i++)
            {
                bwriter.Write((byte)token[i]);
            }
            bwriter.Write((byte)0);
        }
        internal static string PadLeft(string input, int cnt, char padding = ' ')
        {
            string output = input;
            for (int len = output.Length; len < cnt; len++)
                output = padding + output;
            return output;
        }
        internal static string PadRight(string input, int cnt, char padding = ' ')
        {
            string output = input;
            for (int len = output.Length; len < cnt; len++)
                output += padding;
            return output;
        }
        internal static string BytesToHex(byte[] bytes)
        {
            StringBuilder hex = new();

            foreach (byte b in bytes)
            {
                var digits = new byte[] { (byte)(b / 0x10), (byte)(b % 0x10) };

                foreach (var digit in digits)
                {
                    if (digit <= 9)
                    {
                        hex.Append(digit.ToString());
                    }
                    else
                    {
                        char abcdef = (char)((digit - 0xA) + (byte)'A');
                        hex.Append(abcdef.ToString());
                    }
                }
            }
            return hex.ToString();
        }
    }
}
