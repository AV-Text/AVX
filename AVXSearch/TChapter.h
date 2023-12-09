///////////////////////////////////////////////////////////
//  TChapter.h
//  Implementation of the Class TChapter
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_83E1859E_E328_4c40_B295_9C616D380578__INCLUDED_)
#define EA_83E1859E_E328_4c40_B295_9C616D380578__INCLUDED_

#include <Serialization.h>
#include <TMatch.h>
#include <vector>

class TChapter//: public ISerialize
{
//private:
//	rapidjson::Document root;

public:
	TChapter(byte num);
	virtual ~TChapter();
	byte chapter_num;
	uint64 total_hits;
	uint64 verse_hits;

	std::vector<TMatch*> matches;

	std::string serialize();
};
#endif // !defined(EA_83E1859E_E328_4c40_B295_9C616D380578__INCLUDED_)
