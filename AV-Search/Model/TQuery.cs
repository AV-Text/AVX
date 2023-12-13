namespace AVSearch
{
	using Blueprint.Blue;
	using AVXLib;
	using System;
	using AVXLib.Framework;
	public class TQuery
	{
		private Blueprint blueprint;

		public TQuery(ref Blueprint blueprint)
		{
			this.blueprint = blueprint;
		}
		public byte book_cnt					{ get; private set; }
		public UInt64 book_hits					{ get; private set; }
		public Dictionary<byte, TBook> books	{ get; private set; }
        public UInt64 chapter_hits				{ get; private set; }
		public UInt32 error_code				{ get; private set; }
		public List<TExpression> expressions	{ get; private set; }
        public UInt64 query_id					{ get; private set; }
		public TSettings settings				{ get; private set; }
        public UInt64 total_hits				{ get; private set; }
        public UInt64 verse_hits				{ get; private set; }
		public List<UInt32> scope				{ get; private set; }

		public string fetch(byte book, byte chapter)
		{
			return string.Empty;
		}

		public bool add_scope(UInt32 spec)
		{
			return false;
		}
		public bool search()
		{
			return false;
		}
	}
}
