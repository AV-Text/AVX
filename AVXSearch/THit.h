///////////////////////////////////////////////////////////
//  TFound.h
//  Implementation of the Class TFound
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
#define EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_

#include <avxgen.h>
#include <TMatch.h>
#include <TQuery.h>

#include <string>
#include <vector>

class AVXFind;
class TQuery;
class THit
{

public:
	THit(TQuery& query, AVXFind& segment, std::string& expression, std::string& fragment, uint32 start, uint32 until);
	virtual ~THit();

	uint32 start;
	uint32 until;

	bool add(TMatch* match);

	std::vector<const TMatch*> matches;
	uint16 expression;
	uint16 fragment;

	TQuery& find();

private:
	TQuery& query;
	AVXFind& segment;
};
#endif // !defined(EA_E07CC064_DC37_4046_A402_A2744A35A453__INCLUDED_)
