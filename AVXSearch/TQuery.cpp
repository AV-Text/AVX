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

bool TQuery::execute(rapidjson::Document& doc)
{
	return false;
}

bool TQuery::fetch(rapidjson::Document& doc, byte book_num)
{
	if (book_num >= 1 && book_num <= 66)
	{
		auto b = book_num - 1;

		if (this->books[b] != nullptr)
		{
			TBook& book = *(this->books[b]);

			auto results = book.fetch_results();
		}
	}
	return false;
}

bool TQuery::add_scope(uint32 spec)
{
	byte book = spec >> 16;

	if (book == 0)
	{
		for (byte idx = 0; idx < 66; idx++)
		{
			this->books[idx] = new TBook(idx+1);
		}
	}
	else if (book >= 1 && book <= 66)
	{
		byte idx = book - 1;

		if (this->books[idx] == nullptr)
		{
			this->books[idx] = new TBook(book);
		}
		return true;
	}
	return false;
}