///////////////////////////////////////////////////////////
//  TMatch.h
//  Implementation of the Class TMatch
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_)
#define EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_

#include <avxgen.h>
#include <string>

class TMatch
{

public:
	TMatch();
	virtual ~TMatch();
	uint32 coordinates;
	std::string feature;

};
#endif // !defined(EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_)
