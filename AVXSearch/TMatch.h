///////////////////////////////////////////////////////////
//  TFound.h
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
#define EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_

#include <Serialization.h>
#include <IBuild.h>
#include <TTag.h>
#include <TQuery.h>

#include <string>
#include <vector>

class TQuery;
class AVXFind;
class TMatch// : public IAssign
{
public:
	TMatch(AVXFind& segment, std::string& expression, std::string& fragment, uint32 start, uint32 until);
	virtual ~TMatch();

	uint32 start;
	uint32 until;

	bool add(TTag* match);

	std::vector<const TTag*> highlights;
	uint16 expression;
	uint16 fragment;

	TQuery& find();

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder);

private:
	TQuery& query;
	AVXFind& segment;
};
#endif // !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
