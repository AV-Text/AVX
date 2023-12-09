///////////////////////////////////////////////////////////
//  TSettings.h
//  Implementation of the Class TSettings
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_)
#define EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_

#include <Serialization.h>
#include <IBuild.h>

class TSettings : public IBuild
{

public:
	TSettings();
	virtual ~TSettings();
	byte fuzzy_lemmata; // 0 (false) or 1 (true)
	byte lexicon;		// 1 | 2 | 3
	byte similarity;	// 0 | 100 | 33 to 99
	uint16 span;		// 0 to 999

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder);
};
#endif // !defined(EA_C8756118_F193_4bca_B874_CA7E2CBF890B__INCLUDED_)
