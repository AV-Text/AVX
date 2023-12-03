///////////////////////////////////////////////////////////
//  TQueryManager.h
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
#define EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_

#include <avxgen.h>
#include "TQuery.h"

class TQueryManager
{
public:
	TQueryManager();
	virtual ~TQueryManager();
	std::map<uint64, TQuery*> queries;

	TQuery * create_query(AVXBlueprint* blueprint);
	ryml::ConstNodeRef* /* map<byte, TChapter> */ fetch_results(byte book);

};
#endif // !defined(EA_F7AA038A_5EC8_49b5_B290_6D09208EE1A2__INCLUDED_)
