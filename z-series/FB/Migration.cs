﻿namespace DigitalAV.Migration
{
    using AVX.FlatBuf;
    using FlatSharp;
    using System;
    using System.IO;
    using System.Text;

    public class ConsoleApp
    {
        private string output;
        private string outputExtent;
        private string baseSDK;
        internal ConsoleApp()
        {
            this.output = @"C:\src\Digital-AV\z-series\FB\content\";
            this.outputExtent = ".avx";
            this.baseSDK = @"C:\src\Digital-AV\z-series\";
        }

        public static void Main()
        {
            var app = new ConsoleApp();
            app.XBook(     "Book",       "Book-Index");
            app.XChapter(  "Chapter",    "Chapter-Index");
            app.XVerse(    "Verse",      "Verse-Index");
            app.XLemma(    "Lemma",      "Lemmata");
            app.XLemmaOOV( "Lemma-OOV",  "Lemmata-OOV");
            app.XLexicon(  "Lexicon",    "Lexicon");
            app.XNames(    "Names",      "Names");
            app.XWordClass("WordClass",  "WordClasses");
            app.XWrit(     "Writ",       "Written");

            Console.WriteLine("Hello, FlatSharp!");
        }
        private string IX(string itype)
        {
            return this.baseSDK + "AV-" + itype + ".ix";
        }
        private string DX(string itype)
        {
            return this.baseSDK + "AV-" + itype + ".dx";
        }
        private string DXI(string itype)
        {
            return this.baseSDK + "AV-" + itype + ".dxi";
        }
        private string ReadByteString(BinaryReader breader, UInt16 maxLen = 24)
        {
            var buffer = new char[maxLen];

            int i = 0;
            byte c = 0;
            for (c = breader.ReadByte(); c != 0 && i < maxLen; c = breader.ReadByte())
                buffer[i++] = (char)c;
            buffer[i] = '\0';
            if (c != 0) for (c = breader.ReadByte(); c != 0; c = breader.ReadByte()) // discard ... this should not happen ... check in debugger
                    Console.WriteLine("Bad stuff!!!");

            return new string(buffer, 0, i);
        }
        private void SaveContent(string otype, byte[] content)
        {
            var file =  this.output + otype + this.outputExtent;
            var fstream = new StreamWriter(file);

            using (var bwriter = new System.IO.BinaryWriter(fstream.BaseStream))
            {
                bwriter.Write(content);
            }
        }
        private void XBook(string itype, string otype)
        {
            var index = new AVXBookIndex() { Index = new List<AVXBook>() };
            string file = IX(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                byte bookNum = 0;
                do
                {
                    bookNum = breader.ReadByte();
                    var chapterCnt = breader.ReadByte();
                    var chapterIdx = breader.ReadUInt16();
                    var bname = breader.ReadBytes(16);
                    var babbr = breader.ReadBytes(12);

                    var name = new StringBuilder();
                    var abbr = new StringBuilder();

                    for (int i = 0; i < bname.Length && bname[i] != 0; i++)
                        name.Append(bname[i]);
                    for (int i = 0; i < babbr.Length && babbr[i] != 0; i++)
                        abbr.Append(bname[i]);

                    var abbreviations = abbr.ToString().Split(',', StringSplitOptions.RemoveEmptyEntries);

                    var book = new AVXBook() { Num = bookNum, ChapterCnt = chapterCnt, ChapterIdx = chapterIdx, Name = name.ToString(), Abbreviations = abbreviations };

                }   while (bookNum < 66);
            }
            var maxBytesNeeded = AVXBookIndex.Serializer.GetMaxSize(index);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXBookIndex.Serializer.Write(content, index);

            SaveContent(otype, content);
        }
        private void XChapter(string itype, string otype)
        {
            var index = new AVXChapterIndex() { Index = new List<AVXChapter>() };
            string file = IX(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                UInt32 writIdx = 0;
                do
                {
                        writIdx  = breader.ReadUInt32();
                    var verseIdx = breader.ReadUInt16();
                    var wordCnt  = breader.ReadUInt16();

                    var chapter = new AVXChapter() { WritIdx = writIdx, VerseIdx = verseIdx, WordCnt = wordCnt };

                }   while (writIdx < 0xC0A56);
            }
            var maxBytesNeeded = AVXChapterIndex.Serializer.GetMaxSize(index);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXChapterIndex.Serializer.Write(content, index);

            SaveContent(otype, content);
        }
        private void XVerse(string itype, string otype)
        {
            var index = new AVXVerseIndex() { Index = new List<AVXVerse>() };
            string file = IX(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                UInt32 recordIdx = 0;
                do
                {
                    var item     = breader.ReadUInt32();
                    var book     = (byte)( item / 0x1000000);
                    var chapter  = (byte)((item / 0x10000) & 0xFF);
                    var verse    = (byte)((item /   0x100) & 0xFF);
                    var wordCnt  = (byte)( item %   0x100);

                    var entry = new AVXVerse() { Book = book, Chapter = chapter, Verse = verse, WordCnt = wordCnt };
                    index.Index.Add(entry);

                }   while (++recordIdx <= 0x797D);
            }  
            var maxBytesNeeded = AVXVerseIndex.Serializer.GetMaxSize(index);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXVerseIndex.Serializer.Write(content, index);

            SaveContent("Verse-Index", content);
        }
        private void XLemma(string itype, string otype)
        {
            var records = new AVXLemmata() { Record = new List<AVXLemma>() };
            string file = DXI(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                for (var pos = breader.ReadUInt32(); pos != 0xFFFFFFFF; pos = breader.ReadUInt32())
                {
                    var wordKey = breader.ReadUInt16();
                    var wordClass = breader.ReadUInt16();
                    var lemmaCount = breader.ReadUInt16();
                    var lemmata = new UInt16[lemmaCount];
                    for (int i = 0; i < lemmaCount; i++)
                        lemmata[i] = breader.ReadUInt16();

                    var entry = new AVXLemma() { Pos = pos, WordKey = wordKey, WordClass = wordClass, Lemma = lemmata };
                    records.Record.Add(entry);
                }
            }
            var maxBytesNeeded = AVXLemmata.Serializer.GetMaxSize(records);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXLemmata.Serializer.Write(content, records);

            SaveContent(otype, content);
        }
        private void XLemmaOOV(string itype, string otype)
        {
            var records = new AVXLemmataOOV() { Oov = new List<AVXLemmaOOV>() };

            string file = DXI(itype);

            var fstream = new StreamReader(file);
            var buffer = new char[24];

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                while (breader.BaseStream.Position < breader.BaseStream.Length)
                {
                    var oovKey = breader.ReadUInt16();

                    int i = 0;
                    byte c = 0;
                    for (c = breader.ReadByte(); c != 0 && i < 24; c = breader.ReadByte())
                        buffer[i++] = (char)c;
                    buffer[i] = '\0';
                    if (c != 0) for (c = breader.ReadByte(); c != 0; c = breader.ReadByte()) // discard ... this should not happen ... check in debugger
                            Console.WriteLine("Bad stuff!!!");

                    var oovString = new string(buffer, 0, i);
                    var entry = new AVXLemmaOOV() { Key = oovKey, Word = oovString };
                    records.Oov.Add(entry);
                }
            }
            var maxBytesNeeded = AVXLemmataOOV.Serializer.GetMaxSize(records);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXLemmataOOV.Serializer.Write(content, records);

            SaveContent(otype, content);
        }
        private void XNames(string itype, string otype)
        {
            var records = new AVXNames() { Record = new List<AVXName>() };

            string file = DXI(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                while (breader.BaseStream.Position < breader.BaseStream.Length - 1)
                {
                    var wkey = breader.ReadUInt16();
                    var meanings = ReadByteString(breader, maxLen: 4096);
                    var meaningArray = meanings.Split('|', StringSplitOptions.RemoveEmptyEntries);

                    var entry = new AVXName() { WordKey = wkey, Meaning = meaningArray };
                    records.Record.Add(entry);
                }
            }
            var maxBytesNeeded = AVXNames.Serializer.GetMaxSize(records);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXNames.Serializer.Write(content, records);

            SaveContent(otype, content);
        }
   
        private void XLexicon(string itype, string otype)
        {
            int line = 1;
            var records = new AVXLexicon() { Lex = new List<AVXLexItem>() };
            string file = DXI(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                while (breader.BaseStream.Position < breader.BaseStream.Length)
                {
                    var entities = breader.ReadUInt16();
                    int posCnt = breader.ReadUInt16();
                    if (posCnt == 0x3117 && line >= 0x3117)
                        break;
                    UInt32[] pos = new UInt32[posCnt];
                    for (int p = 0; p < posCnt; p++)
                        pos[p] = breader.ReadUInt32();

                    var search  = ReadByteString(breader);
                    var display = ReadByteString(breader);
                    var modern  = ReadByteString(breader);

                    if (!string.IsNullOrEmpty(search))
                    {
                        if (!string.IsNullOrEmpty(display))
                        {
                            if (!string.IsNullOrEmpty(modern))
                                records.Lex.Add(new AVXLexItem() { Search = search, Display = display, Modern = modern, Entities = entities, Pos = pos });
                            else
                                records.Lex.Add(new AVXLexItem() { Search = search, Display = display,                  Entities = entities, Pos = pos });
                        }
                        else if (!string.IsNullOrEmpty(modern))
                                records.Lex.Add(new AVXLexItem() { Search = search,                    Modern = modern, Entities = entities, Pos = pos });
                        else
                                records.Lex.Add(new AVXLexItem() { Search = search,                                     Entities = entities, Pos = pos });
                    }
                    line++;
                }
            }
            var maxBytesNeeded = AVXLexicon.Serializer.GetMaxSize(records);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXLexicon.Serializer.Write(content, records);

            SaveContent(otype, content);
        }
        private void XWordClass(string itype, string otype)
        {
            var records = new AVXWordClasses() { Instance = new List<AVXWordClass>() };
            string file = DXI(itype);

            var fstream = new StreamReader(file);

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                while (breader.BaseStream.Position < breader.BaseStream.Length - 1)
                {
                    var wclass = breader.ReadUInt16();
                    var posCnt = breader.ReadUInt16();
                    var pos = new UInt32[posCnt];
                    for (int i = 0; i < posCnt; i++)
                        pos[i] = breader.ReadUInt32();

                    var entry = new AVXWordClass() { WordClass = wclass, Pos = pos };
                    records.Instance.Add(entry);
                }
            }
            var maxBytesNeeded = AVXWordClasses.Serializer.GetMaxSize(records);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXWordClasses.Serializer.Write(content, records);

            SaveContent(otype, content);
        }
        private void XWrit(string itype, string otype)
        {
            var items = new AVXWritten() { Writ = new List<AVXWrit>() };

            string file = DX(itype);

            var fstream = new StreamReader(file);
            var buffer = new char[24];

            using (var breader = new System.IO.BinaryReader(fstream.BaseStream))
            {
                while (breader.BaseStream.Position < breader.BaseStream.Length-1)
                {
                    var entry = new AVXWrit()
                    {
                        Strongs  = breader.ReadUInt64(),
                        VerseIdx = breader.ReadUInt16(),
                        Word     = breader.ReadUInt16(),
                        Punc     = breader.ReadByte(),
                        Trans    = breader.ReadByte(),
                        Pnwc     = breader.ReadUInt16(),
                        Pos      = breader.ReadUInt32(),
                        Lemma    = breader.ReadUInt16()
                    };
                    items.Writ.Add(entry);
                }
            }
            var maxBytesNeeded = AVXWritten.Serializer.GetMaxSize(items);
            byte[] content = new byte[maxBytesNeeded];
            int bytesWritten = AVXWritten.Serializer.Write(content, items);

            SaveContent(otype, content);
        }
    }
}