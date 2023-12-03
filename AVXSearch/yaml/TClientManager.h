///////////////////////////////////////////////////////////
//  TClientManager.h
//  Implementation of the Class TClientManager
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_)
#define EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_

#include "TQueryManager.h"

class TClientManager
{

public:
	TClientManager();
	virtual ~TClientManager();
	std::map<uint128, TQueryManager*> clients;

	// returns yaml of TQuery:
	const char* create_query(uint128 client_guid, char yaml_blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata);

	// returns yaml of TQuery::books[book].fetch_results():
	const char* fetch_results(uint128 client_guid, byte book);

	void release_client(uint128 client_quid);
	void release_query(uint128 client_quid, uint64 query_id);

};
#endif // !defined(EA_36732251_A4F4_46b0_B9B8_642CCE3A147B__INCLUDED_)
