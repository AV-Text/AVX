///////////////////////////////////////////////////////////
//  TExpression.h
//  Implementation of the Class TExpression
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_F636EEA9_3AA6_4889_8764_D28957F21DC8__INCLUDED_)
#define EA_F636EEA9_3AA6_4889_8764_D28957F21DC8__INCLUDED_

#include <Serialization.h>
#include <string>
#include <vector>
#include <IBuild.h>

#include <AVXFind.h>
#include <TFragment.h>

class TExpression : public IBuild
{
public:
	TExpression(AVXFind& exp, uint16 exp_idx);
	virtual ~TExpression();

	std::vector<TFragment*> fragments;
	std::string expression;
	uint16 expression_idx;

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder);
};
#endif // !defined(EA_F636EEA9_3AA6_4889_8764_D28957F21DC8__INCLUDED_)
