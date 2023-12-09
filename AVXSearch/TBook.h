///////////////////////////////////////////////////////////
//  TBook.h
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_0419B987_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_)
#define EA_0419B987_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_

#include <IBuild.h>

#include <TChapter.h>
#include <map>

class TBook: public IBuild
{
public:
	TBook(byte num);
	virtual ~TBook();
	byte book_hits;
	byte book_num;
	byte chapter_cnt;
	uint64 chapter_hits;
	uint64 total_hits;
	uint64 verse_hits;

	std::map<byte, uint64> verse_hits_by_chapter;
	std::string fetch(byte chapter_num);

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder);

private:
	std::map<byte, TChapter*> chapters;

};

#endif // !defined(EA_0419B9book_num;87_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_)