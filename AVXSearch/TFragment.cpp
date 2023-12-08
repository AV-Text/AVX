///////////////////////////////////////////////////////////
//  TFragment.cpp
//  Implementation of the Class TFragment
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TFragment.h"
#include <AVXFragment.h>

TFragment::TFragment(const AVXFragment* frag)
{

}

TFragment::~TFragment()
{
	for (auto option : this->all_of)
	{
		delete option;
	}
}