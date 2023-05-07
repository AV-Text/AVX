#include <book.h>
#include <md5.h>
#include <inttypes.h>

const char AVXBook::empty[1] = { 0 };

struct OmegaBookRepair {
public:
	const uint8     num;
	const char      name[17];
	const char      abbr2[3];  // strlen == 2 || strlen == 0
	const char      abbr3[4];  // strlen == 3
	const char      abbr4[5];  // <-- Most common // use this for display // strlen <= 4
	const char* abbrAltA;  // Alternate Abbreviation: unknown size
	const char* abbrAltB;  // Alternate Abbreviation: unknown size
};

uint32 OmegaVersion = 0x3507;
OmegaBookRepair BOOKS[] = {
	{  0, "Omega 3.5.07", "35", "o35", "Ω35", "", "" },
	{  1, "Genesis", "Ge", "Gen", "Gen", "Gn", "",  },
	{  2, "Exodus", "Ex", "Exo", "Exo", "Exod", "",  },
	{  3, "Leviticus", "Le", "Lev", "Lev", "Lv", "",  },
	{  4, "Numbers", "Nu", "Num", "Numb", "Nb", "",  },
	{  5, "Deuteronomy", "Dt", "D't", "Deut", "De", "",  },
	{  6, "Joshua", "Js", "Jsh", "Josh", "Jos", "",  },
	{  7, "Judges", "Jg", "Jdg", "Judg", "Jdgs", "",  },
	{  8, "Ruth", "Ru", "Rth", "Ruth", "Rut", "",  },
	{  9, "1 Samuel", "1S", "1Sm", "1Sam", "1Sa", "",  },
	{ 10, "2 Samuel", "2S", "2Sm", "2Sam", "1Sa", "",  },
	{ 11, "1 Kings", "1K", "1Ki", "1Kgs", "1Kg", "1Kin",  },
	{ 12, "2 Kings", "2K", "2Ki", "2Kgs", "2Kg", "2Kin",  },
	{ 13, "1 Chronicles", "", "1Ch", "1Chr", "1Chron", "",  },
	{ 14, "2 Chronicles", "", "2Ch", "2Chr", "2Chron", "",  },
	{ 15, "Ezra", "", "Ezr", "Ezra", "", "",  },
	{ 16, "Nehemiah", "Ne", "Neh", "Neh", "", "",  },
	{ 17, "Esther", "Es", "Est", "Est", "Esth", "",  },
	{ 18, "Job", "Jb", "Job", "Job", "", "",  },
	{ 19, "Psalms", "Ps", "Psa", "Pslm", "Psm", "Pss",  },
	{ 20, "Proverbs", "Pr", "Pro", "Prov", "Prv", "",  },
	{ 21, "Ecclesiastes", "Ec", "Ecc", "Eccl", "Eccle", "Qoh",  },
	{ 22, "Song of Solomon", "So", "SoS", "Song", "SS", "Cant",  },
	{ 23, "Isaiah", "Is", "Isa", "Isa", "", "",  },
	{ 24, "Jeremiah", "Je", "Jer", "Jer", "Jeremy", "Jr",  },
	{ 25, "Lamentations", "La", "Lam", "Lam", "", "",  },
	{ 26, "Ezekiel", "", "Eze", "Ezek", "Ezk", "",  },
	{ 27, "Daniel", "Da", "Dan", "Dan", "Dn", "",  },
	{ 28, "Hosea", "Ho", "Hos", "Hos", "", "",  },
	{ 29, "Joel", "Jl", "Jol", "Joel", "Joe", "",  },
	{ 30, "Amos", "Am", "Amo", "Amos", "", "",  },
	{ 31, "Obadiah", "Ob", "Obd", "Obad", "", "",  },
	{ 32, "Jonah", "", "Jnh", "Jona", "", "",  },
	{ 33, "Micah", "Mc", "Mic", "Mica", "Mi", "",  },
	{ 34, "Nahum", "Na", "Nah", "Nah", "", "",  },
	{ 35, "Habakkuk", "Hb", "Hab", "Hab", "", "",  },
	{ 36, "Zephaniah", "Zp", "Zep", "Zeph", "Zph", "",  },
	{ 37, "Haggai", "Hg", "Hag", "Hag", "", "",  },
	{ 38, "Zechariah", "Zc", "Zec", "Zech", "Zch", "",  },
	{ 39, "Malachi", "Ml", "Mal", "Mal", "", "",  },
	{ 40, "Matthew", "Mt", "Mat", "Matt", "", "",  },
	{ 41, "Mark", "Mk", "Mrk", "Mark", "Mk", "Mr",  },
	{ 42, "Luke", "Lk", "Luk", "Luke", "Lu", "",  },
	{ 43, "John", "Jn", "Jhn", "John", "Joh", "",  },
	{ 44, "Acts", "Ac", "Act", "Acts", "Ats", "",  },
	{ 45, "Romans", "Ro", "Rom", "Rom", "Rm", "",  },
	{ 46, "1 Corinthians", "", "1Co", "1Cor", "", "",  },
	{ 47, "2 Corinthians", "", "2Co", "2Cor", "", "",  },
	{ 48, "Galatians", "Ga", "Gal", "Gal", "", "",  },
	{ 49, "Ephesians", "Ep", "Eph", "Eph", "", "",  },
	{ 50, "Philippians", "Pp", "Php", "Phil", "Philip", "",  },
	{ 51, "Colossians", "Co", "Col", "Col", "", "",  },
	{ 52, "1 Thessalonians", "", "1Th", "1Th", "1Thess", "",  },
	{ 53, "2 Thessalonians", "", "2Th", "2Th", "2Thess", "",  },
	{ 54, "1 Timothy", "", "1Ti", "1Tim", "", "",  },
	{ 55, "2 Timothy", "", "2Ti", "2Tim", "", "",  },
	{ 56, "Titus", "Ti", "Ti", "Ti", "", "",  },
	{ 57, "Philemon", "Pm", "Phm", "Phm", "Philem", "",  },
	{ 58, "Hebrews", "", "Heb", "Heb", "Hbr", "Hbrs",  },
	{ 59, "James", "Jm", "Jam", "Jam", "", "",  },
	{ 60, "1 Peter", "1P", "1Pe", "1Pet", "1Pt", "",  },
	{ 61, "2 Peter", "2P", "2Pe", "2Pet", "2Pt", "",  },
	{ 62, "1 John", "1J", "1Jn", "1Jn", "1Jn", "1Jhn",  },
	{ 63, "2 John", "2J", "2Jn", "2Jn", "1Jn", "1Jhn",  },
	{ 64, "3 John", "3J", "3Jn", "3Jn", "1Jn", "1Jhn",  },
	{ 65, "Jude", "Jd", "Jd", "Jude", "", "",  },
	{ 66, "Revelation", "Re", "Rev", "Rev", "", "",  }
};

bool reset_omega(DirectoryContent* directory)
{
	uint8* root = reinterpret_cast<uint8*>(directory);
	uint8* raw = reinterpret_cast<uint8*>(root + directory[1].content_offset);
	for (uint8 b = 0; b <= 66; b++, raw += 48)
	{
		auto replacement = BOOKS[b];
		auto book = reinterpret_cast<BookContent*>(raw);
		book->verse_count = book->writ_count;
		*((uint32*)&book->writ_count) = b > 0 ? book->writ_index : OmegaVersion;

		auto bookName16 = (char*)&((&book->writ_count)[1]);
		auto a2 = bookName16 + 16;
		auto a3 = a2 + 3;
		auto a4 = a3 + 4;
		auto alts = a4 + 5;

		int len = Strnlen(replacement.name, 16);
		Strncpy(bookName16, replacement.name, len);
		for (int i = len; len < 16; len++)
			bookName16[len] = 0;

		len = Strnlen(replacement.abbr2, 2);
		Strncpy(a2, replacement.abbr2, len);
		for (int i = len; len < 3; len++)
			a2[len] = 0;

		len = Strnlen(replacement.abbr3, 3);
		Strncpy(a3, replacement.abbr3, len);
		for (int i = len; len < 4; len++)
			a3[len] = 0;

		len = Strnlen(replacement.abbr4, 4);
		Strncpy(a4, replacement.abbr4, len);
		for (int i = len; len < 5; len++)
			a4[len] = 0;

		len = 0;
		int lenA = Strnlen(replacement.abbrAltA, 9);
		if (lenA > 0)
		{
			Strncpy(alts, replacement.abbrAltA, lenA);
			alts[lenA++] = 0;
			int lenB = Strnlen(&(replacement.abbrAltA[lenA]), 9 - lenA);

			if (lenB > 0)
			{
				Strncpy(alts + lenA, replacement.abbrAltB, lenB);
				alts[lenA + lenB++] = 0;
			}
			len = lenA + lenB;
		}
		for (int i = len; i < 10; i++)
			alts[i] = 0;
	}
	for (int i = 1; i <= 7; i++)
	{
		auto hash = md5(root + directory[i].content_offset, directory[i].content_length, directory[i].content_hash[0], directory[i].content_hash[1]);
		printf("%d:\t%" PRIX64 "\t%" PRIX64 "\n", i, directory[i].content_hash[0], directory[i].content_hash[1]);
	}
	return true;
}
