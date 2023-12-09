///////////////////////////////////////////////////////////
//  TExpression.cpp
//  Implementation of the Class TExpression
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TExpression.h"
#include "TFragment.h"
#include <AVXFind.h>

TExpression::TExpression(AVXFind& exp)
{
	this->segment = exp.expression;

	for (auto frag : exp.fragments)
	{
		TFragment* fragment = new TFragment(*frag);
		this->fragments.push_back(fragment);
	}
}

TExpression::~TExpression()
{
	for (auto fragment : this->fragments)
	{
		delete fragment;
	}
}

void TExpression::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{
	builder.StartObject();

	builder.Key("segment");
	builder.String(segment.c_str());

	builder.Key("fragments");
	builder.StartArray();
	for (TFragment* frag : this->fragments)
	{
		frag->build(builder);
	}
	builder.EndArray();

	builder.EndObject();
}
