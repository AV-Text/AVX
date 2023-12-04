namespace AVXFramework
{
    using System.Runtime.InteropServices;
    using System.Text;
    using System.Text.Unicode;
    using YamlDotNet.Core.Tokens;

    public class NativeLibrary
    {
        // AVX-Search:
        [DllImport("AVXSearch.dll", CharSet = CharSet.Ansi)]
        private static extern UInt64 create_query(UInt64 client_id_1, UInt64 client_id_2, string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);
        [DllImport("AVXSearch.dll", CharSet = CharSet.Ansi)]
        private static extern string create_query_and_execute(UInt64 client_id_1, UInt64 client_id_2, string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);
        [DllImport("AVXSearch.dll")]
        private static extern byte add_scope(UInt64 client_id_1, UInt64 client_id_2, UInt64 query_id, byte book, byte chapter, byte verse);
        [DllImport("AVXSearch.dll", CharSet = CharSet.Ansi)]
        private static extern string execute(UInt64 client_id_1, UInt64 client_id_2, UInt64 query_id);
        [DllImport("AVXSearch.dll", CharSet = CharSet.Ansi)]
        private static extern string fetch_results(UInt64 client_id_1, UInt64 client_id_2, UInt64 query_id, byte book);
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
        internal UInt64 create_query(string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
        {
            var result = NativeLibrary.create_query(this.ClientId_1, this.ClientId_2, yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);
            return result;
        }
        internal string create_query_and_execute(string yaml_blueprint, UInt16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
        {
            var result = NativeLibrary.create_query_and_execute(this.ClientId_1, this.ClientId_2, yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);
            return result;
        }
        internal string fetch_results(UInt64 query_id, byte book)
        {
            return NativeLibrary.fetch_results(this.ClientId_1, this.ClientId_2, query_id, book);
        }
        internal bool add_scope(UInt64 query_id, byte book, byte chapter, byte verse)
        {
            return NativeLibrary.add_scope(this.ClientId_1, this.ClientId_2, query_id, book, chapter, verse) == (byte)1 ? true : false;
        }
        internal string execute(UInt64 query_id)
        {
            return NativeLibrary.execute(this.ClientId_1, this.ClientId_2, query_id);
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
        private UInt64 Address;
        public string Summary { get; private set; } // This is the YAML representation of the TQuery object

        public NativeStatement(string omega)  // (full path-spec to omega file)
        {
            byte[] omega_utf8 = System.Text.Encoding.UTF8.GetBytes(omega);
            this.AVXTextData = NativeLibrary.create_avxtext(omega_utf8);
            this.External = new NativeLibrary();
            this.Address = 0; // we need to extract this from the yaml/result
            this.Summary = string.Empty;
        }
        public bool Search(string blueprint, UInt16 span, byte lexicon, byte similarity, bool fuzzy_lemmata, List<(byte book, byte chapter, byte verse)> scope)
        {
            this.Free();
            this.Summary = string.Empty;

            if (scope.Count == 0)
            {
                // TO DO (TODO):
                // this.yaml = this.External.create_query_and_execute(blueprint, span, lexicon, similarity, fuzzy_lemmata ? (byte)1 : (byte)0);
                // this.address = from the desrialized yaml
                // brute force

                this.Address = this.External.create_query(blueprint, span, lexicon, similarity, fuzzy_lemmata ? (byte)1 : (byte)0);
                this.Summary = this.External.execute(this.Address);
            }
            else
            {
                this.Address = this.External.create_query(blueprint, span, lexicon, similarity, fuzzy_lemmata ? (byte)1 : (byte)0);
                foreach (var spec in scope)
                {
                    this.External.add_scope(this.Address, spec.book, spec.chapter, spec.verse);
                }
                this.Summary = this.External.execute(this.Address);
            }
            return (this.Address != 0 && !string.IsNullOrWhiteSpace(this.Summary));
        }
        public string Fetch(UInt64 client_id, byte book)
        {
            this.Summary = this.External.fetch_results(this.Address, book);

            return this.Summary;
        }
        public void Free()
        {
            if (this.Address != 0)
                this.External.release_query(this.Address);
            this.Address = 0;
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
