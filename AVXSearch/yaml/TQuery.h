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

#include <ryml.hpp>

class TQuery
{

public:
	TQuery(ryml::ConstNodeRef blueprint, uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);

	virtual ~TQuery();
	byte book_cnt;
	uint64 book_hits;
	TBook books[66];
	uint64 chapter_hits;
	uint32 error_code;
	TExpression expressions;
	uint64 query_id;
	TSettings settings;
	uint64 total_hits;
	uint64 verse_hits;

private:
	ryml::ConstNodeRef blueprint;

};
#endif // !defined(EA_1A9DEEE5_474E_4a0f_BC44_4C27249CBC6A__INCLUDED_)
