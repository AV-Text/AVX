///////////////////////////////////////////////////////////
//  TFound.h
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
#define EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_

#include <avxgen.h>
#include "TMatch.h"

#include <string>

class TFound
{

public:
	TFound();
	virtual ~TFound();
	std::string fragment;
	uint64 match_cnt;
	TMatch matches;
	uint32 start;
	uint32 until;
	TMatch *m_TMatch;

};
#endif // !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
