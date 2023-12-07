///////////////////////////////////////////////////////////
//  TQuery.h
//  Implementation of the Class TQuery
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_)
#define EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_

#include <avxgen.h>

#include "TBook.h"
#include "TExpression.h"
#include "TSettings.h"

#include <string>
#include <map>

#include <rapidjson/document.h>
#include <AVXBlueprint.h>

#include <map>

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
	TExpression expressions;
	uint64 query_id;
	TSettings settings;
	uint64 total_hits;
	uint64 verse_hits;
	std::vector<uint32> scope;

	bool execute(rapidjson::Document& doc);
	bool fetch(rapidjson::Document& doc, byte book);

	bool add_scope(uint32 spec);
};
#endif // !defined(EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_)
