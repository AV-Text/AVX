///////////////////////////////////////////////////////////
//  TQuery.cpp
//  Implementation of the Class TQuery
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TQuery.h"

TQuery::~TQuery(){

}

TQuery::TQuery(AVXBlueprint* blueprint)
{
	this->blueprint = blueprint;
}