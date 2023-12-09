///////////////////////////////////////////////////////////
//  TQuery.h
//  Implementation of the Class TQuery
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_)
#define EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_

#include <Serialization.h>

#include <string>
#include <map>

#include "TSettings.h"
#include <AVXBlueprint.h>

#include <vector>
class TExpression;
class TChapter;
class TBook;

class TQuery
{
private:
	AVXBlueprint* blueprint;

public:
	TQuery(AVXBlueprint* blueprint);

	virtual ~TQuery();
	byte book_cnt;
	uint64 book_hits;
	std::map<byte, TBook*> books;
	uint64 chapter_hits;
	uint32 error_code;
	std::vector<TExpression*> expressions;
	uint64 query_id;
	TSettings settings;
	uint64 total_hits;
	uint64 verse_hits;
	std::vector<uint32> scope;

	std::string fetch(byte book, byte chapter);

	bool add_scope(uint32 spec);

	std::string serialize();
};
#endif // !defined(EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_)
