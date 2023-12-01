///////////////////////////////////////////////////////////
//  TSettings.h
//  Implementation of the Class TSettings
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_)
#define EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_

#include <avxgen.h>

class TSettings
{

public:
	TSettings();
	virtual ~TSettings();
	byte fuzzy_lemata;
	byte /* 1 | 2 |  3 */ lexicon;
	byte /* 0 | 100 | 33 to 99 */ similarity;
	uint16 /* 0 to 999 */ span;

};
#endif // !defined(EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_)
