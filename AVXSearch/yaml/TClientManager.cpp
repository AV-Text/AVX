///////////////////////////////////////////////////////////
//  TClientManager.cpp
//  Implementation of the Class TClientManager
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TClientManager.h"

#define RYML_SINGLE_HDR_DEFINE_NOW
#include <ryml.hpp>


TClientManager::TClientManager(){

}

TClientManager::~TClientManager(){

}

std::string /* yaml of TQuery */ TClientManager::create_query(uint128 client_guid, std::string yaml_blueprint, uint16 span, byte lexicon, byte similarity, byte fuzzy_lemmata){

	return  NULL;
}

std::string /* yaml of TQuery::books[book].fetch_results() */ TClientManager::fetch_results(uint128 client_guid, byte book){

	return  NULL;
}

void TClientManager::release_client(uint128 client_quid){

}

void TClientManager::release_query(uint128 client_quid, uint64 query_id){

}