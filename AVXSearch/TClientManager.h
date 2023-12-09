///////////////////////////////////////////////////////////
//  TClientManager.h
//  Implementation of the Class TClientManager
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_)
#define EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_

#include <TQueryManager.h>
#include <TQuery.h>

class TClientManager
{

public:
	TClientManager();
	virtual ~TClientManager();
	std::map<uint128, TQueryManager*> clients;

	TQuery* query_create(uint128 client_guid, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);
	bool query_scope_add(uint128 client_guid, uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to);

	// returns json of TQuery:
	std::string fetch(uint128 client_guid, uint64 query_id);

	// returns json of TChapter:
	std::string fetch(uint128 client_id, uint64 query_id, byte book, byte chapter);

	void client_release(uint128 client_guid);
	void query_release(uint128 client_guid, uint64 query_id);

};
#endif // !defined(EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_)
