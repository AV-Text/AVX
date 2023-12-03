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

TQuery * TQueryManager::create_query(AVXBlueprint* blueprint)
{
	auto query = new TQuery(blueprint);
	auto query_id = uint64(query);
	this->queries[query_id] = query; // we don't really need a map for this, but it is the current design
	
	return query;
}

ryml::ConstNodeRef* /* map<byte, TChapter> */ TQueryManager::fetch_results(byte book)
{

	return  nullptr;
}