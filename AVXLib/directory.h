#pragma once
#include <avxgen.h>
#include <XVMem.h>

#pragma pack(4)
struct DirectoryContentStruct
{
	char   content_label[16];
	uint32 content_offset;
	uint32 content_length;
	uint32 record_length;	// 0 when variable-length
	uint32 record_count;
	uint64 content_hash[2];
};
typedef struct DirectoryContentStruct DirectoryContent;

#pragma pack(1)
struct WrittenContentStruct
{
	uint16 strongs[4];
	uint8  b;
	uint8  c;
	uint8  v;
	uint8  wc;
	uint16 wkey;
	uint8  punc;
	uint8  tran;
	uint16 pn_pos12;
	uint32 pos32;
	uint16 lemma;
};
typedef struct WrittenContentStruct WrittenContent;

#pragma pack(1)
struct BookContentStruct
{
	uint8  num;
	uint8  chapter_count;
	uint16 chapter_index;
	uint16 verse_count;	// 0 when variable-length
	uint32 writ_count;
	char   name[16];	// book_name
	char   abbr2[2];
	char   abbr3[3];
	char   abbr4[4];
	char   abbr_alt[9];
};
typedef struct BookContentStruct BookContent;

#pragma pack(1)
struct ChapterContentStruct
{
	uint16 writ_index;
	uint16 writ_count;
	uint8  book_num;
	uint8  verse_count;
};
typedef struct ChapterContentStruct ChapterContent;

#pragma pack(2)
struct LemmataContentStruct
{
	uint32 pos32;
	uint16 wkey;
	uint16 pn_pos12;
	uint16 lemma_count;
	uint16* lemmata;;
};
typedef struct LemmataContentStruct LemmataContent;

struct OOVContentStruct
{
	uint32 oov_key;
	char*  oov_word;
};
typedef struct OOVContentStruct OOVContent;

#pragma pack(2)
struct LexiconContentStruct // variable length
{
	uint16 entities;
	uint16 size;
	uint32* pos; // followed by char*search, char*display, char*modern
};
typedef struct LexiconContentStruct LexiconContent;

#pragma pack(2)
struct NamesContentStruct
{
	uint16 wkey;
	char*  meanings; // pipe-delimited + null-terminated
};
typedef struct NamesContentStruct NamesContent;

class directory: private XVMem<const uint8>
{
public:
	directory(const char* omega);
	const DirectoryContent const * contents;
	inline bool isOkay()
	{
		return this->ok;
	}
	inline explicit operator const BookContent* ()		const { return this->ok ? this->book :    nullptr; }
	inline explicit operator const ChapterContent* ()	const { return this->ok ? this->chapter : nullptr; }
	inline explicit operator const WrittenContent* ()	const { return this->ok ? this->written : nullptr; }
	inline explicit operator const LexiconContent* ()	const { return this->ok ? this->lexicon : nullptr; }
	inline explicit operator const LemmataContent* ()	const { return this->ok ? this->lemmata : nullptr; }
	inline explicit operator const OOVContent* ()		const { return this->ok ? this->oov :     nullptr; }
	inline explicit operator const NamesContent* ()		const { return this->ok ? this->names :   nullptr; }

private:
	WrittenContent		* written;
	BookContent			* book;
	ChapterContent		* chapter;
	LexiconContent		* lexicon;
	LemmataContent		* lemmata;
	OOVContent			* oov;
	NamesContent		* names;
	bool                  ok;
};

