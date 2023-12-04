///////////////////////////////////////////////////////////
//  TBook.h
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_0419B987_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_)
#define EA_0419B987_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_

#include <avxgen.h>
#include "TChapter.h"

#include <map>

class TBook
{

public:
	TBook(byte num);
	virtual ~TBook();
	byte book_cnt;
	byte book_hits;
	byte book_num;
	byte chapter_cnt;
	uint64 chapter_hits;
	uint64 total_hits;
	uint64 verse_hits;

	std::map<byte, TChapter*> fetch_results();

private:
	std::map<byte, TChapter*> chapters;

};
#endif // !defined(EA_0419B987_84CB_472f_AF4F_C75C5A86A7D3__INCLUDED_)
