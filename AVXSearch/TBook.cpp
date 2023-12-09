///////////////////////////////////////////////////////////
//  TBook.cpp
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TBook.h>
#include <map>

TBook::TBook(byte num)
{
	this->book_num = (num >= 1 && num <= 66) ? num : 0;

	// TO DO (TODO): call AVXText to fill other properties
}

TBook::~TBook()
{

}

std::string TBook::fetch(byte chapter_num)
{
	auto chapter = this->chapters.find(chapter_num);

	return chapter != this->chapters.end() ? chapter->second->serialize() : "";
}

void TBook::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{
	builder.StartObject();
	// TO DO: populate
	builder.EndObject();
}
