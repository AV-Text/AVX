#include "directory.h"
#include <book.h>
#include <md5.h>

/*static*/ AVXBook* AVXBook::Book[67] = {nullptr};
static const uint64 omega_hash[2] = { 0xCA33BDA541F799BE, 0x6AB95A2150DE55CA };

directory::directory(const char* omega) : contents((const DirectoryContent const*) this->Acquire(omega, false, true)),
	book(nullptr), chapter(nullptr), written(nullptr), lexicon(nullptr), lemmata(nullptr), oov(nullptr), names(nullptr)
{
	this->ok = true;

	for (int i = 1; i <= 7; i++)
	{
		switch (contents[i].content_hash[0])
		{
		case 0xFB5C1A08F8774486: this->ok = (contents[i].content_hash[1] == 0xE6A0049A899042F6); // book hash
								 if (this->ok)
									this->book = (BookContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->book = nullptr;
								 break;
		case 0x29D5C0D1AFF79C95: this->ok = (contents[i].content_hash[1] == 0xBE3A964891126FBE); // chapter hash
								 if (this->ok)
									this->chapter = (ChapterContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->chapter = nullptr;
								 break;
		case 0xA1F54F560E73511D: this->ok = (contents[i].content_hash[1] == 0xA77DCDB91A85EFDB); // written hash
								 if (this->ok)
									this->written = (WrittenContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->written = nullptr;
								 break;
		case 0xF1C7694D3C5B15A5: this->ok = (contents[i].content_hash[1] == 0x26845D7A4946BDFE); // lexicon hash
								 if (this->ok)
									this->lexicon = (LexiconContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lexicon = nullptr;
								 break;
		case 0xB64F907ABC54470F: this->ok = (contents[i].content_hash[1] == 0x2D227D8AC5703E33); // lemmata hash
								 if (this->ok)
									this->lemmata = (LemmataContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->lemmata = nullptr;
								 break;
		case 0xADEA45027082EC56: this->ok = (contents[i].content_hash[1] == 0xEA59B079EF94C96F); // oov-lemmata hash
								 if (this->ok)
									this->oov = (OOVContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->oov = nullptr;
								 break;
		case 0xB7885CB9C8F0293A: this->ok = (contents[i].content_hash[1] == 0x3845818BD5A4DCEC); // names hash
								 if (this->ok)
									this->names = (NamesContent*) (((uint8*) this->contents) + contents[i].content_offset);
								 else
									this->names = nullptr;
								 break;

		default:                 this->ok = false;
		}
		if (this->ok)
		{
			MD5 hash;
			hash.update(((const unsigned char*)(this->contents)) + contents[i].content_offset, contents[i].content_length);
			this->ok = (hash.U64high() == contents[i].content_hash[0]) && (hash.U64low() == contents[i].content_hash[1]);
		}
		if (!this->ok)
		{
			break;
		}
	}
	if (ok)
	{
		new AVXBook(this->book[0], nullptr, nullptr, this->contents);

		auto chap = const_cast<ChapterContent*>(this->chapter);
		auto writ = const_cast<WrittenContent*>(this->written);

		for (uint8 b = 1; b <= 66; b++)
		{
			new AVXBook(this->book[b], chap, writ, this->contents);
			chap += this->book[b].chapter_count;
			writ += this->book[b].writ_count;
		}
	}
}


