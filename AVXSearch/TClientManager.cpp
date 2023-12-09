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
extern "C" __declspec(dllexport) uint64 query_create(uint64 client_id1, uint64 client_id2, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
{
	uint128 client_id(client_id1, client_id2);
	return uint64(ClientManager.query_create(client_id, blueprint, span, lexicon, similarity, fuzzy_lemmata));
}

extern "C" __declspec(dllexport) byte query_add_scope(uint64 client_id1, uint64 client_id2, uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to)
{
	uint128 client_id(client_id1, client_id2);
	return ClientManager.query_scope_add(client_id, query_id, book, chapter, verse_from, verse_to) ? byte(1) : byte(0);
}

extern "C" __declspec(dllexport) const char* query_fetch(uint64 client_id1, uint64 client_id2, uint64 query_id)
{
	uint128 client_id(client_id1, client_id2);

//	if (ClientManager.execute(client_id, query_id))
	{
		;
	}

	// TO DO (TODO): Serialize tree into json string

	return EMPTY;
}

extern "C" __declspec(dllexport) const char* chapter_fetch(uint64 client_id1, uint64 client_id2, uint64 query_id, byte book, byte chapter)
{
	uint128 client_id(client_id1, client_id2);
	rapidjson::Document doc;

	//if (ClientManager.fetch(client_id, query_id, book, chapter))
	{
		;
	}

	// TO DO (TODO): Serialize tree into json string

	return EMPTY;
}

extern "C" __declspec(dllexport) void client_release(uint64 client_id1, uint64 client_id2)
{
	uint128 client_id(client_id1, client_id2);
	ClientManager.client_release(client_id);
}

extern "C" __declspec(dllexport) void query_release(uint64 client_id1, uint64 client_id2, uint64 query_id)
{
	uint128 client_id(client_id1, client_id2);
	ClientManager.query_release(client_id, query_id);
}

TClientManager::TClientManager(){

}

TClientManager::~TClientManager(){

}

TQuery* TClientManager::query_create(uint128 client_id, char blueprint[], uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata)
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
	TQuery* query = qmgr->create(oo_blueprint);
	/* TO DO: json serialization (TODO) */
	return  nullptr;
}

bool TClientManager::query_scope_add(uint128 client_id, uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->add_scope(query_id, book, chapter, verse_from, verse_to);
	}
	return false;
}

std::string TClientManager::fetch(uint128 client_id, uint64 query_id)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->fetch(query_id);
	}
	return "";
}


std::string TClientManager::fetch(uint128 client_id, uint64 query_id, byte book, byte chapter)
{
	TQueryManager* qmgr = nullptr;
	auto candidate = this->clients.find(client_id);
	if (candidate != this->clients.end())
	{
		qmgr = candidate->second;

		return qmgr->fetch(query_id, book, chapter);
	}
	return "";
}

void TClientManager::client_release(uint128 client_id)
{
	;
}

void TClientManager::query_release(uint128 client_quid, uint64 query_id)
{
	;
}