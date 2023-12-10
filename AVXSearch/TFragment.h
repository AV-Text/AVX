///////////////////////////////////////////////////////////
//  TFragment.h
//  Implementation of the Class TFragment
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_)
#define EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_

#include <Serialization.h>
#include <string>
#include <vector>
#include <IBuild.h>
#include <AVXFragment.h>
#include <TOptions.h>

class TFragment : public IBuild
{

public:
	TFragment(const AVXFragment& frag, uint16 frag_idx);
	virtual ~TFragment();
	uint64 hits;
	bool anchored;
	std::string fragment;
	uint16 fragment_idx;
	std::vector<TOptions*> all_of;

	const AVXFragment& fragment_avx;
	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder);
};
#endif // !defined(EA_463021B4_CF2F_4648_B191_F5E59539632B__INCLUDED_)
