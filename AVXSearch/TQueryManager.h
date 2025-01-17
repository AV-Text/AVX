///////////////////////////////////////////////////////////
//  TQueryManager.h
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
#define EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_

#include <avxgen.h>
#include <AVXFind.h>
#include "TQuery.h"

class TQueryManager
{
public:
	TQueryManager();

	virtual ~TQueryManager();
	std::map<uint64, TQuery*> queries;

	TQuery* create(AVXBlueprint* blueprint);
	bool add_scope(uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to);
	std::string fetch(uint64 query_id);
	std::string fetch(uint64 query_id, byte book, byte chapter);
};
#endif // !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
