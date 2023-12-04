///////////////////////////////////////////////////////////
//  TQueryManager.h
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
#define EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_

#include <avxgen.h>
#include "TQuery.h"

class TQueryManager
{
public:
	TQueryManager();
	virtual ~TQueryManager();
	std::map<uint64, TQuery*> queries;

	TQuery* initialize(AVXBlueprint* blueprint);
	bool add_scope(uint64 query_id, byte book, byte chapter, byte verse);
	ryml::ConstNodeRef* execute(uint64 query_id);
	ryml::ConstNodeRef* /* map<byte, TChapter> */ fetch_results(uint64 query_id, byte book);

};
#endif // !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
