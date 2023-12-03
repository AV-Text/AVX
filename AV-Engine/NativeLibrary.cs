using System;

namespace AVXFramework
{
    using AVXLib.Memory;
    using Blueprint.Blue;
    using System.Runtime.InteropServices;
    using System.Text;

    internal class NativeLibrary
    {
        // OBSOLETE:
        [DllImport("AVXSearch.dll")]
        public static extern UInt64 create_statement(string buffer);

        [DllImport("AVXSearch.dll")]
        public static extern IntPtr exec_statement(UInt64 address);

        [DllImport("AVXSearch.dll")]
        public static extern Int32 free_statement(UInt64 address);

        // AVX-Search:
        [DllImport("AVXSearch.dll")]
        private static extern string create_query(UInt64 client_id_1, UInt64 client_id_2, string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);
        [DllImport("AVXSearch.dll")]
        private static extern string fetch_results(UInt64 client_id_1, UInt64 client_id_2, byte book);
        [DllImport("AVXSearch.dll")]
        private static extern void release_client(UInt64 client_id_1, UInt64 client_id_2);
        [DllImport("AVXSearch.dll")]
        private static extern void release_query(UInt64 client_id_1, UInt64 client_id_2, UInt64 query_id);

        private UInt64 ClientId_1
        {
            get
            {
                byte[] bytes = this.ClientId.ToByteArray();
                UInt64 result = 0;

                for (int i = 0; i < 64; i++)
                {
                    result <<= 8;
                    result |= bytes[i];
                }
                return result;
            }
        }
        private UInt64 ClientId_2
        {
            get
            {
                byte[] bytes = this.ClientId.ToByteArray();
                UInt64 result = 0;

                for (int i = 64; i < 128; i++)
                {
                    result <<= 8;
                    result |= bytes[i];
                }
                return result;
            }
        }
        private Guid ClientId;
        public NativeLibrary()
        {
            this.ClientId = new Guid();
        }
        public string create_query(string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
        {
            return NativeLibrary.create_query(this.ClientId_1, this.ClientId_2, yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);
        }
        public string fetch_results(byte book)
        {
            return NativeLibrary.fetch_results(this.ClientId_1, this.ClientId_2, book);
        }
        public void release_client()
        {
            NativeLibrary.release_client(this.ClientId_1, this.ClientId_2);
        }
        public void release_query(UInt64 queryId) // QueryId is in the payload returned by create_query
        {
            NativeLibrary.release_query(this.ClientId_1, this.ClientId_2, queryId);
        }

        // AVX-Text
        [DllImport("AVXSearch.dll")]
        public static extern UInt64 create_avxtext(byte[] path);

        [DllImport("AVXSearch.dll")]
        public static extern void free_avxtext(UInt64 data);
    }

    public class NativeStatement
    {
        private UInt64 address;
        private IntPtr? executed;
        public NativeStatement(string blueprint)
        {
            this.address = NativeLibrary.create_statement(blueprint);
            this.executed = NativeLibrary.exec_statement(this.address);
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
