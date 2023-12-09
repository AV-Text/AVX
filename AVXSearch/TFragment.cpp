///////////////////////////////////////////////////////////
//  TFragment.cpp
//  Implementation of the Class TFragment
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TFragment.h>
#include <TOption.h>
#include <AVXFragment.h>

TFragment::TFragment(const AVXFragment& frag)
{
	this->anchored = frag.anchored ;
	this->fragment = frag.fragment["fragment"].GetString();

	for (auto option : frag.requirements)
	{
		this->all_of.push_back(new TOption(*option));
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
	// TO DO: populate
	builder.EndObject();
}