using FlatSharp;
using System.Runtime.InteropServices;
using System.Text;
using XBlueprintBlue;

namespace AVXFramework
{
    internal class NativeLibrary
    {
        [DllImport("AVXSearch.dll")]
        public static extern UInt64 create_statement(byte[] buffer);

        [DllImport("AVXSearch.dll")]
        public static extern IntPtr exec_statement(UInt64 address);

        [DllImport("AVXSearch.dll")]
        public static extern Int32 free_statement(UInt64 address);

        [DllImport("AVXSearch.dll")]
        public static extern UInt64 create_avxtext(byte[] path);

        [DllImport("AVXSearch.dll")]
        public static extern void free_avxtext(UInt64 data);
    }

    public class NativeStatement
    {
        private UInt64 address;
        private IntPtr? executed;
        public NativeStatement(XBlueprint blueprint)
        {
            int maxBytesNeeded = XBlueprint.Serializer.GetMaxSize(blueprint);
            byte[] bytes = new byte[maxBytesNeeded];
            int bytesWritten = XBlueprint.Serializer.Write(bytes, blueprint);

            if (bytesWritten > 0)
            {
                this.address = NativeLibrary.create_statement(bytes);
                this.executed = NativeLibrary.exec_statement(this.address);
            }
        }
        public void Free()
        {
            if (this.address != 0)
                NativeLibrary.free_statement(this.address);
            this.address = 0;
            this.executed = null;
        }
        ~NativeStatement()
        {
            this.Free();
        }
    }
    public class NativeText
    {
        private UInt64 address;
        public NativeText(byte[] path)
        {
            this.address = NativeLibrary.create_avxtext(path);
        }
        public void Free()
        {
            if (this.address != 0)
                NativeLibrary.free_avxtext(this.address);
            this.address = 0;
        }
        ~NativeText()
        {
            this.Free();
        }
    }
}
