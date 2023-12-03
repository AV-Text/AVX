namespace AVXFramework
{
    using System.Runtime.InteropServices;
    using YamlDotNet.Core.Tokens;

    public class NativeLibrary
    {
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

                for (int i = 0; i < 8; i++)
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

                for (int i = 8; i < 16; i++)
                {
                    result <<= 8;
                    result |= bytes[i];
                }
                return result;
            }
        }
        private Guid ClientId;
        internal NativeLibrary()
        {
            this.ClientId = new Guid();
        }
        internal string create_query(string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
        {
            return NativeLibrary.create_query(this.ClientId_1, this.ClientId_2, yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);
        }
        internal string fetch_results(byte book)
        {
            return NativeLibrary.fetch_results(this.ClientId_1, this.ClientId_2, book);
        }
        internal void release_client()
        {
            NativeLibrary.release_client(this.ClientId_1, this.ClientId_2);
        }
        internal void release_query(UInt64 queryId) // QueryId is in the payload returned by create_query
        {
            NativeLibrary.release_query(this.ClientId_1, this.ClientId_2, queryId);
        }

        // AVX-Text
        [DllImport("AVXSearch.dll")]
        internal static extern UInt64 create_avxtext(byte[] path);

        [DllImport("AVXSearch.dll")]
        internal static extern void free_avxtext(UInt64 data);
    }

    public class NativeStatement
    {
        private UInt64 AVXTextData;
        private NativeLibrary External;
        private UInt64 address;
        private string yaml; // temproary until deeper integration is implemented

        public NativeStatement(string omega)  // (full path-spec to omega file)
        {
            // this.address = NativeLibrary.create_statement(blueprint);
            // this.executed = NativeLibrary.exec_statement(this.address);

            byte[] omega_utf8 = System.Text.Encoding.UTF8.GetBytes(omega);
            this.AVXTextData = NativeLibrary.create_avxtext(omega_utf8);
            this.External = new NativeLibrary();
            this.address = 0; // we need to extract this from the yaml/result
            this.yaml = string.Empty;
        }
        public string Search(string blueprint, UInt16 span, byte lexicon, byte similarity, bool fuzzy_lemmata)
        {
            this.Free();
            this.address = 0; // we need to extract this from the yaml/result
            this.yaml = this.External.create_query(blueprint, span, lexicon, similarity, fuzzy_lemmata ? (byte)1 : (byte)0);

            return this.yaml;
        }
        public string Fetch(byte book)
        {
            this.Free();
            this.address = 0; // we need to extract this from the yaml/result
            this.yaml = this.External.fetch_results(book);

            return this.yaml;
        }
        public void Free()
        {
            if (this.address != 0)
                this.External.release_query(this.address);
            this.address = 0;
        }
        public void Release()
        {
            this.Free();
            NativeLibrary.free_avxtext(this.AVXTextData);
        }
        ~NativeStatement()
        {
            this.Release();
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
