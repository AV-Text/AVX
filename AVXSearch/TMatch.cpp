///////////////////////////////////////////////////////////
//  TFound.cpp
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TQuery.h>
#include <TExpression.h>
#include <TMatch.h>

TMatch::TMatch(TExpression& expression, TFragment& fragment, uint32 start, uint32 until): query(query), segment(segment), expression(expression), fragment(fragment)
{
    this->start = start;
    this->until = until;
}

TMatch::~TMatch()
{

}

bool TMatch::add(TTag* match)
{
    if (match != nullptr)
    {
        this->highlights.push_back(match);

        if (match->coordinates < this->start)
        {
            this->start = match->coordinates;
        }
        if (match->coordinates > this->until)
        {
            this->until = match->coordinates;
        }
        return true;
    }
    return false;
}

void TMatch::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{/*
    std::vector<const TTag*> highlights;*/

    builder.StartObject();

    builder.Key("start");
    builder.Uint(this->start);

    builder.Key("until");
    builder.Uint(this->until);

    builder.Key("fragment_idx");
    builder.Uint(this->fragment.fragment_idx);

    builder.Key("expression_idx");
    builder.Uint(this->expression.expression_idx);

    builder.Key("highlights");
    builder.StartArray();
    for (auto tag : this->highlights)
    {
        tag->build(builder);
    }
    builder.EndArray();

    builder.EndObject();
}
