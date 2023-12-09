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

	builder.Key("book_num");
	builder.Uint(this->book_num); // get this value from scope

	builder.Key("book_hits");
	builder.Uint64(this->book_hits);

	builder.Key("chapter_cnt");
	builder.Uint64(this->chapter_cnt);

	builder.Key("chapter_hits");
	builder.Uint64(this->chapter_hits);

	builder.Key("total_hits");
	builder.Uint64(this->total_hits);

	builder.Key("verse_hits");
	builder.Uint64(this->verse_hits);

	builder.Key("verse_hits_by_chapter");
	builder.StartArray();
	for (auto hits = this->verse_hits_by_chapter.begin(); hits != this->verse_hits_by_chapter.end(); ++hits)
	{
		byte chapter_num = hits->first;
		uint64 cnt = hits->second;

		builder.StartObject();
		builder.Key("chapter_num");
		builder.Uint(chapter_num);
		builder.Key("verse_hits");
		builder.Uint64(cnt);
		builder.EndObject();
	}
	builder.EndArray();

	builder.EndObject();
}
