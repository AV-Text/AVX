///////////////////////////////////////////////////////////
//  TFound.cpp
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TQuery.h>
#include <TExpression.h>
#include <TMatch.h>

TMatch::TMatch(AVXFind& segment, std::string& expression, std::string& fragment, uint32 start, uint32 until): query(query), segment(segment)
{
    this->start = start;
    this->until = until;

    TExpression* found = nullptr;
    int e = 0;
    for (auto exp : query.expressions)
    {
        if (exp->segment == expression)
        {
            this->expression = e;
            found = exp;
            break;
        }
        e++;
    }
    if (found != nullptr)
    {
        int f = 0;
        for (auto frag : found->fragments)
        {
            if (frag->fragment == fragment)
            {
                this->fragment = f;
                break;
            }
            f++;
        }
    }
    else
    {
        this->expression = 0;
        this->fragment = 0;
    }
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

    builder.Key("fragment");
    builder.Uint(this->fragment);

    builder.Key("expression");
    builder.Uint(this->expression);

    builder.Key("highlights");
    builder.StartArray();
    for (auto tag : this->highlights)
    {
        tag->build(builder);
    }
    builder.EndArray();

    builder.EndObject();
}
