///////////////////////////////////////////////////////////
//  TFragment.cpp
//  Implementation of the Class TFragment
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TFragment.h>
#include <TOptions.h>
#include <AVXFragment.h>

TFragment::TFragment(const AVXFragment& frag, uint16 frag_idx)
{
	this->anchored = frag.anchored ;
	this->fragment = frag.fragment["fragment"].GetString();
	this->fragment_idx = frag_idx;

	uint16 idx = 0;
	for (auto option : frag.requirements)
	{
		this->all_of.push_back(new TOptions(*option, idx++));
	}
}

TFragment::~TFragment()
{
	for (auto option : this->all_of)
	{
		delete option;
	}
}

void TFragment::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{
	builder.StartObject();

	builder.Key("fragment");
	builder.String(this->fragment.c_str());

	builder.Key("fragment_idx");
	builder.Uint(this->fragment_idx);

	builder.Key("anchored");
	builder.Bool(this->anchored);

	builder.Key("all_of");
	builder.StartArray();
	for (auto option : this->all_of)
	{
		option->build(builder);
	}
	builder.EndArray();

	builder.EndObject();
}