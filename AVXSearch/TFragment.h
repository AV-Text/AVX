///////////////////////////////////////////////////////////
//  TFragment.h
//  Implementation of the Class TFragment
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_)
#define EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_

#include <avxgen.h>
#include <string>
#include <vector>
#include <AVXFragment.h>
#include <TOption.h>

class TFragment
{

public:
	TFragment(const AVXFragment& frag);
	~TFragment();
	uint64 hits;
	bool anchored;
	std::string fragment;
	std::vector<TOption*> all_of;
};
#endif // !defined(EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_)
