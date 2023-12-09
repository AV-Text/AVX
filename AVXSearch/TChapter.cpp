///////////////////////////////////////////////////////////
//  TChapter.cpp
//  Implementation of the Class TChapter
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TChapter.h>

#include <Serialization.h>

TChapter::TChapter(byte num): chapter_num(num)
{

}

TChapter::~TChapter()
{

}

std::string TChapter::serialize()
{
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> builder(sb);

	builder.StartObject();

	builder.Key("chapter_num");
	builder.Uint(this->chapter_num);

	builder.Key("total_hits");
	builder.Uint64(this->total_hits);

	builder.Key("verse_hits");
	builder.Uint64(this->verse_hits);

	builder.Key("matches");
	builder.StartArray();
	for (TMatch* match : this->matches)
	{
		match->build(builder);
	}
	builder.EndArray();

	return sb.GetString();
}