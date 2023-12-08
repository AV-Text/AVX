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

	TQuery* initialize(AVXBlueprint* blueprint);
	bool add_scope(uint64 query_id, byte book, byte chapter, byte verse);
	bool execute(rapidjson::Document&, uint64 query_id);
	bool fetch_results(rapidjson::Document&, uint64 query_id, byte book);

	bool search_quoted(TQuery& query, AVXFind& segment);
	bool search_unquoted(TQuery& query, AVXFind& segment);

	inline const bool find(TQuery& query, AVXFind& segment)
	{
		bool found = segment.quoted ? search_quoted(query, segment) : search_unquoted(query, segment);
		return found;
	}

};
#endif // !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
