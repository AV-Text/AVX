#include "AVXPuncComparator.h"
#include <stdlib.h>

uint16 AVXPuncComparator::compare(const WrittenContent& writ, TMatch& match, TTag& tag)
{
	bool positive = !this->negate;
	uint8 punc = this->punc;
	uint8 mask = (punc & writ.punc);

	bool result = positive ? (punc == mask) : (punc != mask);
	return result ? AVXComparator::FullMatch : 0;
}

AVXPuncComparator::AVXPuncComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node), punc((byte)node["pos32"].GetUint())
{
	;
}

AVXPuncComparator::~AVXPuncComparator()
{
	;
}