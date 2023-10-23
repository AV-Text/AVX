#pragma once
#include <avxgen.h>
#include <XVMem.h>

extern "C" uint32 DIR_cnt;
extern "C" uint32 WRIT_cnt;
extern "C" uint32 BOOK_cnt;
extern "C" uint32 CHAPTER_cnt;
extern "C" uint32 LEMMA_cnt;
extern "C" uint32 LEX_cnt;
extern "C" uint32 NAME_cnt;
extern "C" uint32 OOV_cnt;


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
	uint16 writ_count;
	uint32 writ_index;
	char   text;	// this is a character-array: book_name[16] + abbreviations[18]
	//char   name[16];
	//char   abbr2[3];
	//char   abbr3[4];
	//char   abbr4[5];
	//char   abbr_alt[10];
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
	uint16 lemmata; // [this is an array of uint16]
};
typedef struct LemmataContentStruct LemmataContent;

#pragma pack(1)
struct OOVContentStruct
{
	uint16 oov_key;
	char   oov_word; // [this is an array of char]
};
typedef struct OOVContentStruct OOVContent;

#pragma pack(2)
struct LexiconContentStruct // variable length
{
	uint16 entities;
	uint16 size;
	uint32 pos; // followed by char*search, char*display, char*modern [this is an array of pos]
};
typedef struct LexiconContentStruct LexiconContent;

#pragma pack(1)
struct NamesContentStruct
{
	uint16 wkey;
	char   meanings; // pipe-delimited + null-terminated [this is an array of char]
};
typedef struct NamesContentStruct NamesContent;

#pragma pack(1)
struct BookContent3201Struct	// Older Omega format
{
	uint8  num;
	uint8  chapter_count;
	uint16 chapter_index;
	uint16 verse_count;
	uint16 writ_count;
	uint32 writ_index;
	char   text;	// this is a character-array: book_name[16] + abbreviations[18]
	//char   name[16];
	//char   abbr2[2];
	//char   abbr3[3];
	//char   abbr4[4];
	//char   abbr_alt[9];
};
typedef struct BookContent3201Struct BookContent3201;

class directory: private XVMem<const uint8>
{
private:
	uint32 version;
public:
	directory(const char* omega);
	~directory();
	const DirectoryContent * contents;
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

