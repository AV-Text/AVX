///////////////////////////////////////////////////////////
//  TFound.cpp
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TFound.h"

TFound::TFound(TQuery& query, AVXFind& segment): query(query), segment(segment)
{
    this->start = 0;
    this->until = 0xFFFFFFFF;
}

TFound::TFound(TQuery& query, AVXFind& segment, uint32 start, uint32 until) : query(query), segment(segment)
{
    this->start = start;
    this->until = until;
}

TFound::~TFound()
{

}

bool TFound::add(TMatch* match)
{
    if (match != nullptr)
    {
        this->matches.push_back(match);

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