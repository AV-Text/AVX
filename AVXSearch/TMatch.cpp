///////////////////////////////////////////////////////////
//  TFound.cpp
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TMatch.h>
#include <TQuery.h>

TMatch::TMatch(TQuery& query, AVXFind& segment, std::string& expression, std::string& fragment, uint32 start, uint32 until) : query(query), segment(segment)
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