///////////////////////////////////////////////////////////
//  TQueryManager.cpp
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TQueryManager.h"

TQueryManager::TQueryManager(){

}

TQueryManager::~TQueryManager(){

}

TQuery * TQueryManager::initialize(AVXBlueprint* blueprint)
{
	auto query = new TQuery(blueprint);
	auto query_id = uint64(query);
	this->queries[query_id] = query; // we don't really need a map for this, but it is the current design

	return query;
}

bool TQueryManager::add_scope(uint64 query_id, byte book, byte chapter, byte verse)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		query->scope.push_back(uint32(book) << 16 | uint32(chapter) << 8 | verse);
		return true;
	}
	return false;
}

bool TQueryManager::execute(rapidjson::Document& doc, uint64 query_id)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		return query->execute(doc);
	}
	return false;
}

// returns tree for map<byte, TChapter>
bool TQueryManager::fetch_results(rapidjson::Document& doc, uint64 query_id, byte book)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		if (book >= 1 && book <= 66 && query->books[book-1] != nullptr)
		{
			auto ibook = query->fetch(doc, book);

			if (iquery != this->queries.end())
			{
				TQuery* query = this->queries[query_id];
				return query->fetch(doc, book);
			}
		}
	}
	return false;
}