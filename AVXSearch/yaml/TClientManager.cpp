///////////////////////////////////////////////////////////
//  TClientManager.cpp
//  Implementation of the Class TClientManager
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TClientManager.h"
#include <AVXBlueprint.h>

#include <rapidjson/document.h>

static TClientManager ClientManager;

static const char* EMPTY = "";

// C API:
extern "C" __declspec(dllexport) uint64 create_query(uint64 client_id1, uint64 client_id2, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	uint128 client_id(client_id1, client_id2);
	return uint64(ClientManager.initialize(client_id, blueprint, span, lexicon, similarity, fuzzy_lemmata));
}

extern "C" __declspec(dllexport) const char* create_query_and_execute(uint64 client_id1, uint64 client_id2, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	uint128 client_id(client_id1, client_id2);
	TQuery* query = ClientManager.initialize(client_id, blueprint, span, lexicon, similarity, fuzzy_lemmata);
	rapidjson::Document doc;

	if (query->execute(doc))
	{
		;
	}

	// TO DO (TODO): Serialize tree into yaml string

	return EMPTY;
}

extern "C" __declspec(dllexport) byte add_scope(uint64 client_id1, uint64 client_id2, uint64 query_id, byte book, byte chapter, byte verse)
{
	uint128 client_id(client_id1, client_id2);
	return ClientManager.add_scope(client_id, query_id, book, chapter, verse) ? byte(1) : byte(2);
}

extern "C" __declspec(dllexport) const char* execute(uint64 client_id1, uint64 client_id2, uint64 query_id)
{
	uint128 client_id(client_id1, client_id2);
	rapidjson::Document doc;

	if (ClientManager.execute(doc, client_id, query_id))
	{
		;
	}

	// TO DO (TODO): Serialize tree into yaml string

	return EMPTY;
}

extern "C" __declspec(dllexport) const char* fetch_results(uint64 client_id1, uint64 client_id2, uint64 query_id, byte book)
{
	uint128 client_id(client_id1, client_id2);
	rapidjson::Document doc;

	if (ClientManager.fetch_results(doc, client_id, query_id, book))
	{
		;
	}

	// TO DO (TODO): Serialize tree into yaml string

	return EMPTY;
}

extern "C" __declspec(dllexport) void release_client(uint64 client_id1, uint64 client_id2)
{
	uint128 client_id(client_id1, client_id2);
	ClientManager.release_client(client_id);
}

extern "C" __declspec(dllexport) void release_query(uint64 client_id1, uint64 client_id2, uint64 query_id)
{
	uint128 client_id(client_id1, client_id2);
	ClientManager.release_query(client_id, query_id);
}

TClientManager::TClientManager(){

}

TClientManager::~TClientManager(){

}

TQuery* TClientManager::initialize(uint128 client_id, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	AVXBlueprint* oo_blueprint = new AVXBlueprint(blueprint, span, lexicon, similarity, fuzzy_lemmata);

	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;
	}
	else
	{
		qmgr = new TQueryManager();
		this->clients.insert(std::make_pair(client_id, qmgr));
	}
	TQuery* query = qmgr->initialize(oo_blueprint);
	/* TO DO: YAML serialization (TODO) */
	return  nullptr;
}

bool TClientManager::add_scope(uint128 client_id, uint64 query_id, byte book, byte chapter, byte verse)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->add_scope(query_id, book, chapter, verse);
	}
	return false;
}

bool TClientManager::execute(rapidjson::Document& doc, uint128 client_id, uint64 query_id)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->execute(doc, query_id);
	}
	return false;
}


bool TClientManager::fetch_results(rapidjson::Document& doc, uint128 client_id, uint64 query_id, byte book)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->fetch_results(doc, query_id, book);
	}
	return false;
}

void TClientManager::release_client(uint128 client_id)
{
	;
}

void TClientManager::release_query(uint128 client_quid, uint64 query_id)
{
	;
}