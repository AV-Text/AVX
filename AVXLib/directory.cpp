#include "directory.h"
#include <book.h>
#include <md5.h>
#include <lexicon.h>
#include <names.h>
#include <oov_lemmata.h>
#include <lemmata.h>
#include <string.h> // for memcpy
#include <stdio.h>
#include <md5.h>
#include <inttypes.h>

uint32 DIR_cnt = 0;
uint32 WRIT_cnt = 0;
uint32 BOOK_cnt = 0;
uint32 CHAPTER_cnt = 0;
uint32 LEMMA_cnt = 0;
uint32 LEX_cnt = 0;
uint32 NAME_cnt = 0;
uint32 OOV_cnt = 0;

/*static*/ AVXBook* AVXBook::Book[67] = {nullptr};
static const uint64 omega_hash[2] = { 0xCA33BDA541F799BE, 0x6AB95A2150DE55CA };

directory::directory(const char* omega) : contents((const DirectoryContent const*) this->Acquire("AVX-Omega", omega, false, true)),
	book(nullptr), chapter(nullptr), written(nullptr), lexicon(nullptr), lemmata(nullptr), oov(nullptr), names(nullptr)
{
	this->ok = true;

	for (int i = 1; i <= 7; i++)
	{
		// There is a bug in the Omega-3.2 content hashes, only the left 64-bits are valid
		// mitigation is to add || true when setting this->ok =
		switch (contents[i].content_hash[0])
		{
		case 0xFB5C1A08F8774486: this->ok = (contents[i].content_hash[1] == 0xE6A0049A899042F6) || true; // book hash
								 if (this->ok)
									this->book = (BookContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->book = nullptr;
								 BOOK_cnt = this->contents[i].record_count;
								 break;
		case 0x29D5C0D1AFF79C95: this->ok = (contents[i].content_hash[1] == 0xBE3A964891126FBE) || true; // chapter hash
								 if (this->ok)
									this->chapter = (ChapterContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->chapter = nullptr;
								 CHAPTER_cnt = this->contents[i].record_count;
								 break;
		case 0xA1F54F560E73511D: this->ok = (contents[i].content_hash[1] == 0xA77DCDB91A85EFDB) || true; // written hash
								 if (this->ok)
									this->written = (WrittenContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->written = nullptr;
								 WRIT_cnt = this->contents[i].record_count;
								 break;
		case 0xF1C7694D3C5B15A5: this->ok = (contents[i].content_hash[1] == 0x26845D7A4946BDFE) || true; // lexicon hash
								 if (this->ok)
									this->lexicon = (LexiconContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lexicon = nullptr;
								 LEX_cnt = this->contents[i].record_count;
								 break;
		case 0xB64F907ABC54470F: this->ok = (contents[i].content_hash[1] == 0x2D227D8AC5703E33) || true; // lemmata hash
								 if (this->ok)
									this->lemmata = (LemmataContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lemmata = nullptr;
								 LEMMA_cnt = this->contents[i].record_count;
								 break;
		case 0xADEA45027082EC56: this->ok = (contents[i].content_hash[1] == 0xEA59B079EF94C96F) || true; // oov-lemmata hash
								 if (this->ok)
									this->oov = (OOVContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->oov = nullptr;
								 OOV_cnt = this->contents[i].record_count;
								 break;
		case 0xB7885CB9C8F0293A: this->ok = (contents[i].content_hash[1] == 0x3845818BD5A4DCEC) || true; // names hash
								 if (this->ok)
									this->names = (NamesContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->names = nullptr;
								 NAME_cnt = this->contents[i].record_count;
								 break;

		default:                 this->ok = false;
		}
		// MD5 hasher is also broken ... skip sheck and debugging on subsequent Omega-3.x release
		if (false) // (this->ok)
		{
//			MD5 hash;
//			hash.update(((const unsigned char*)(this->contents)) + contents[i].content_offset, contents[i].content_length);
//			this->ok = (hash.U64high() == contents[i].content_hash[0]) && (hash.U64low() == contents[i].content_hash[1]);
		}
		if (!this->ok)
		{
			DIR_cnt = this->contents[0].record_count;
			break;
		}
	}
	if (this->ok)
	{
		create_lexicon(this->lexicon, LEX_cnt);

		this->version = this->book[0].writ_index;

		auto chap = const_cast<ChapterContent*>(this->chapter);
		auto writ = const_cast<WrittenContent*>(this->written);

		for (uint8 b = 1; b <= 66; b++)
		{
			uint8* raw = reinterpret_cast<uint8*>(this->book) + (48 * b);
			BookContent* bk = reinterpret_cast<BookContent*>(raw);
			BookContent& ref = *bk;
			new AVXBook(ref, chap, writ, this->contents); // This adds it to the static array of books
			chap += bk->chapter_count;
			writ += bk->writ_count;
		}

		::lemmata_lookup = new AVXLemmata(this->lemmata, ::LEMMA_cnt);
		::lemmata_oov = new AVXLemmaOOV(this->oov, ::OOV_cnt);
		::name_lookup = new AVXNames(this->names, ::NAME_cnt);

		size_t size = 0;
		for(int i = 0; i < this->contents[0].record_count; i++)
		{
			size += this->contents[i].content_length;
		}
		uint8* buffer = (uint8*) calloc(size, sizeof(uint8));
		memcpy(buffer, this->contents, size);

		reset_omega(reinterpret_cast<DirectoryContent*>(buffer));

		#
		auto file = fopen("omega35.data", "wb");
		fwrite(buffer, sizeof(uint8), size, file);
		fclose(file);
		uint64 hi, lo;
		auto hash = md5(buffer, size, hi, lo);
		printf("omega:\t%" PRIX64 "\t%" PRIX64 "\n", hi, lo);

	}
}

directory::~directory()
{
	for (uint8 b = 0; b <= 66; b++)
	{
		const AVXBook& bk = AVXBook::GetBook(b);
		delete& bk;
	}
	delete_lexicon();

	delete ::lemmata_lookup;
	delete ::lemmata_oov;
	delete ::name_lookup;
}