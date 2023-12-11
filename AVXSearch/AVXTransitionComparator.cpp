#include "AVXTransitionComparator.h"
#include <stdlib.h>

uint16 AVXTransitionComparator::compare(const WrittenContent& writ, TMatch& match, TTag& tag)
{
	bool positive = !this->negate;
	uint8 tran = this->tran;
	uint8 mask = (tran & writ.tran);

	bool result = positive ? (tran == mask) : (tran != mask);
	return result ? AVXComparator::FullMatch : 0;
}

AVXTransitionComparator::AVXTransitionComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node), tran((byte)node["pos32"].GetUint())
{
	;
}

AVXTransitionComparator::~AVXTransitionComparator()
{
	;
}