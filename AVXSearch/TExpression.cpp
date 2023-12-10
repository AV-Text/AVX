///////////////////////////////////////////////////////////
//  TExpression.cpp
//  Implementation of the Class TExpression
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TExpression.h"
#include "TFragment.h"
#include <AVXFind.h>

TExpression::TExpression(AVXFind& exp, uint16 exp_idx)
{
	this->expression = exp.expression;
	this->expression_idx = exp_idx;

	uint16 idx = 0;
	for (auto frag : exp.fragments)
	{
		TFragment* fragment = new TFragment(*frag, idx++);
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

	builder.Key("expression");
	builder.String(expression.c_str());

	builder.Key("expression_idx");
	builder.Uint(expression_idx);

	builder.Key("fragments");
	builder.StartArray();
	for (TFragment* frag : this->fragments)
	{
		frag->build(builder);
	}
	builder.EndArray();

	builder.EndObject();
}
