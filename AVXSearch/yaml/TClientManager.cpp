///////////////////////////////////////////////////////////
//  TClientManager.cpp
//  Implementation of the Class TClientManager
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TClientManager.h"
#include <AVXBlueprint.h>

static TClientManager ClientManager;

// C API:
extern "C" const char* create_query(uint64 client_guid_1, uint64 client_guid_2, char yaml_blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	uint128 client_guid(client_guid_1, client_guid_2);
	return ClientManager.create_query(client_guid, yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);
}

extern "C" const char* fetch_results(uint64 client_guid_1, uint64 client_guid_2, byte book)
{
	uint128 client_guid(client_guid_1, client_guid_2);
	return ClientManager.fetch_results(client_guid, book);
}

extern "C" void release_client(uint64 client_guid_1, uint64 client_guid_2)
{
	uint128 client_guid(client_guid_1, client_guid_2);
	ClientManager.release_client(client_guid);
}

extern "C" void release_query(uint64 client_guid_1, uint64 client_guid_2, uint64 query_id)
{
	uint128 client_guid(client_guid_1, client_guid_2);
	ClientManager.fetch_results(client_guid, query_id);
}

// OBSOLETE !!!
extern "C" const char* const avx_create_search(const char* const request)
{/*
	AVXBlueprint search(request);
	search.execute();
	auto results = search.build();
	if (results != nullptr)
	{
		MemoryTable.insert(reinterpret_cast<uintptr_t>(results));
	}
	return results;*/
	return nullptr;
}

// OBSOLETE !!!
extern "C" bool avx_delete_search(const char* const* results)
{/*
	auto entry = reinterpret_cast<uintptr_t>(results);
	auto memory = reinterpret_cast<char*>(entry);

	auto it = MemoryTable.find(entry);
	if (it != MemoryTable.end()) {
		MemoryTable.erase(it);
		free(memory);
		return true;
	}*/
	return false;
}

TClientManager::TClientManager(){

}

TClientManager::~TClientManager(){

}

const char* TClientManager::create_query(uint128 client_guid, char yaml_blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	AVXBlueprint* blueprint = new AVXBlueprint(yaml_blueprint, span, lexicon, similarity, fuzzy_lemmata);

	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_guid);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;
	}
	else
	{
		qmgr = new TQueryManager();
		this->clients.insert(std::make_pair(client_guid, qmgr));
	}
	TQuery* query = qmgr->create_query(blueprint);
	/* TO DO: YAML serialization (TODO) */
	return  nullptr;
}

const char* TClientManager::fetch_results(uint128 client_guid, byte book)
{
	return  NULL;
}

void TClientManager::release_client(uint128 client_quid)
{
	;
}

void TClientManager::release_query(uint128 client_quid, uint64 query_id)
{
	;
}