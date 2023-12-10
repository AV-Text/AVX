///////////////////////////////////////////////////////////
//  TQueryManager.cpp
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TQueryManager.h>
#include <AVXFragment.h>
#include <AVXBlueprint.h>
#include <AVXFind.h>
#include <TBook.h>
#include <TMatch.h>
#include <TTag.h>
#include <map>
#include <directory.h>
#include <book.h>

TQueryManager::TQueryManager(){

}

TQueryManager::~TQueryManager(){

}

TQuery * TQueryManager::create(AVXBlueprint* blueprint)
{
	auto query = new TQuery(blueprint);
	auto query_id = uint64(query);
	this->queries[query_id] = query; // we don't really need a map for this, but it is the current design

	return query;
}

bool TQueryManager::add_scope(uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];

        uint32 verse_range = 0;
        if (verse_from != 0)
        {
            verse_range = uint32(verse_from) << 24 + uint32(verse_to) << 16;
        }
		query->scope.push_back(uint32(book) << 16 | uint32(chapter) << 8 | verse_range);
		return true;
	}
	return false;
}

std::string TQueryManager::fetch(uint64 query_id)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		return query->serialize();
	}
    return "";
}

// returns tree for map<byte, TChapter>
std::string TQueryManager::fetch(uint64 query_id, byte book, byte chapter)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		if (book >= 1 && book <= 66 && query->books[book-1] != nullptr)
		{
			auto result = query->fetch(book, chapter);

            return result;
		}
	}
    return "";
}
