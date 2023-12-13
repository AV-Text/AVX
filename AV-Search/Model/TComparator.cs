namespace AVSearch
{
    using Blueprint.Blue;
    using AVXLib;
    using System;
    using AVXLib.Framework;

    public interface IComparator
    {
        abstract UInt16 compare(ref Written writ, ref TMatch match, ref TTag tag);
    }
    public class TComparator: IComparator, IFeature
    {
        private TComparator(ref QFeature feature, bool bad)
        {
            this.Okay = false;
        }
        protected TComparator(ref QFeature feature)
        {
            this.Okay = true;
        }
        public static TComparator Create(ref QFeature feature)
        {
            return new TComparator(ref feature, false);
        }

        public virtual UInt16 compare(ref Written writ, ref TMatch match, ref TTag tag)
        {
            return 0;
        }
        public bool Okay        { get; private set;   }
        public string Type      { get; protected set; }
        public string Text      { get; protected set; }
        public bool Negate      { get; protected set; }
                              
        public QFeature Feature { get; protected set; }
        public Written Writ     { get; protected set; }
        public TMatch Match     { get; protected set; }
        public TTag Tag         { get; protected set; }
                              
        const UInt16 FullMatch = 1000;  // 100%
    }
}

