#include "directory.h"
#include <book.h>
#include <md5.h>
#include <lexicon.h>
#include <names.h>
#include <oov_lemmata.h>
#include <lemmata.h>
#include <string.h> // for memcpy
#include <md5.h>

directory* directory::GLOBAL = nullptr;
const uint16 directory::ExpectedPlateRevision = 3911;
const uint16 directory::LibraryRevision = 3993; // 3930 + 31 [oct] + 30 [nov] + 2 [dec] // should have been hex :-| 2.0.3.C02 // B = November (overflow after 8 Dec)

extern "C" __declspec(dllexport) uint64 create_avxtext(const char* data)
{
	if (data != nullptr)
	{
		directory::GLOBAL = new directory(data); // e.g. "C:\\src\\AVX\\omega\\AVX-Omega-3911.data"
//		auto lex = (LexiconContent*)(directory::GLOBAL);
//		AVXLexTokenMap::create_lexicon(lex, lex->pos + 1, true);
		return uint64(directory::GLOBAL);
	}
	return 0;
}

extern "C" __declspec(dllexport) void free_avxtext(uint64 data)
{
	if (data == uint64(directory::GLOBAL) && data != 0)
	{
		AVXLexTokenMap::delete_lexicon();
		delete directory::GLOBAL;
		directory::GLOBAL = nullptr;
	}
}

uint32 DIR_cnt = 0;
uint32 WRIT_cnt = 0;
uint32 BOOK_cnt = 0;
uint32 CHAPTER_cnt = 0;
uint32 LEMMA_cnt = 0;
uint32 LEX_cnt = 0;
uint32 NAME_cnt = 0;
uint32 OOV_cnt = 0;
uint32 PHONE_cnt = 0;

/*static*/ AVXBook* AVXBook::Book[67] = {nullptr};
static const uint64 omega_hash[2] = { 0x90B73F90B8AED72C, 0xEF0325411C00C4FE };

directory::directory(const char* omega) : contents((const DirectoryContent*) this->Acquire("AVX-Omega", omega, false, true)),
	book(nullptr), chapter(nullptr), written(nullptr), lexicon(nullptr), lemmata(nullptr), oov(nullptr), names(nullptr)
{
	this->ok = true;
	bool force_upgrade = false;
	DIR_cnt = this->contents[0].record_count;

	for (int i = 1; i < int(DIR_cnt); i++)
	{
		// There is a bug in the Omega-3.2 content hashes, only the left 64-bits are valid
		// mitigation is to add || true when setting this->ok =
		switch (contents[i].content_hash[0])
		{
		case 0xFB5C1A08F8774486: force_upgrade = true;
								 this->ok = false;
								 BOOK_cnt = this->contents[i].record_count;
								 break;
		case 0xC665903E2C634AE8: this->ok = (contents[i].content_hash[1] == 0x3C591FED81F4A67A); // book hash
								 if (this->ok)
									this->book = (BookContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->book = nullptr;
								 BOOK_cnt = this->contents[i].record_count;
								 break;
		case 0x29D5C0D1AFF79C95: this->ok = (contents[i].content_hash[1] == 0xBE3A964891126FBE); // chapter hash
								 if (this->ok)
									this->chapter = (ChapterContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->chapter = nullptr;
								 CHAPTER_cnt = this->contents[i].record_count;
								 break;
		case 0xA1F54F560E73511D: this->ok = (contents[i].content_hash[1] == 0xA77DCDB91A85EFDB); // written hash
								 if (this->ok)
									this->written = (WrittenContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->written = nullptr;
								 WRIT_cnt = this->contents[i].record_count;
								 break;
		case 0xF1C7694D3C5B15A5: this->ok = (contents[i].content_hash[1] == 0x26845D7A4946BDFE); // lexicon hash
								 if (this->ok)
									this->lexicon = (LexiconContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lexicon = nullptr;
								 LEX_cnt = this->contents[i].record_count;
								 break;
		case 0xB64F907ABC54470F: this->ok = (contents[i].content_hash[1] == 0x2D227D8AC5703E33); // lemmata hash
								 if (this->ok)
									this->lemmata = (LemmataContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lemmata = nullptr;
								 LEMMA_cnt = this->contents[i].record_count;
								 break;
		case 0xADEA45027082EC56: this->ok = (contents[i].content_hash[1] == 0xEA59B079EF94C96F); // oov-lemmata hash
								 if (this->ok)
									this->oov = (OOVContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->oov = nullptr;
								 OOV_cnt = this->contents[i].record_count;
								 break;
		case 0xB7885CB9C8F0293A: this->ok = (contents[i].content_hash[1] == 0x3845818BD5A4DCEC); // names hash
								 if (this->ok)
									this->names = (NamesContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->names = nullptr;
								 NAME_cnt = this->contents[i].record_count;
								 break;
		case 0x78A31E514E3292EA: this->ok = (contents[i].content_hash[1] == 0xF0C7ED99D199CDFF); // names hash
								 if (this->ok)
									this->phonetics = (PhoneticContent*)(((uint8*)this->contents) + contents[i].content_offset);
								 else
									this->phonetics = nullptr;
								 PHONE_cnt = this->contents[i].record_count;
								 break;
		default:                 this->ok = false;
		}
		if (!this->ok)
		{
			break;
		}
	}
	if (this->ok)	// check has of entire contents, if it checks oout, then it's all good
	{
		size_t size = 0;
		for (int i = 0; i < int(this->contents[0].record_count); i++)
		{
			size += this->contents[i].content_length;
		}
		const uint8* root = reinterpret_cast<uint8*>(const_cast<DirectoryContent*>(this->contents));
		uint64 hi, lo;
		auto hash = md5(root, size, hi, lo);

		this->ok = (omega_hash[0] == hi) && (omega_hash[1] == lo);
	}
	if (this->ok)
	{
		AVXLexTokenMap::create_lexicon(this->lexicon, LEX_cnt, false);

		this->version = this->book[0].writ_index;
		new AVXBook(this->book[0], nullptr, nullptr, this->contents);

		auto chap = const_cast<ChapterContent*>(this->chapter);
		auto writ = const_cast<WrittenContent*>(this->written);

		for (uint8 b = 1; b <= 66; b++)
		{
			uint8* raw = reinterpret_cast<uint8*>(this->book) + (48 * b);
			BookContent* bk = reinterpret_cast<BookContent*>(raw);
			new AVXBook(*bk, chap, writ, this->contents); // This adds it to the static array of books
			chap += bk->chapter_count;
			writ += bk->writ_count;
		}

		::lemmata_lookup = new AVXLemmata(this->lemmata, ::LEMMA_cnt);
		::lemmata_oov = new AVXLemmaOOV(this->oov, ::OOV_cnt);
		::name_lookup = new AVXNames(this->names, ::NAME_cnt);
	}
	else if (force_upgrade)
	{
		size_t size = 0;
		for (int i = 0; i < int(this->contents[0].record_count); i++)
		{
			size += this->contents[i].content_length;
		}
		uint8* buffer = (uint8*)calloc(size, sizeof(uint8));
		memcpy(buffer, this->contents, size);
		reset_omega(reinterpret_cast<DirectoryContent*>(buffer), size);
	}
}

directory::~directory()
{
	for (uint8 b = 0; b <= 66; b++)
	{
		const AVXBook& bk = AVXBook::GetBook(b);
		delete& bk;
	}
	AVXLexTokenMap::delete_lexicon();

	delete ::lemmata_lookup;
	delete ::lemmata_oov;
	delete ::name_lookup;
}