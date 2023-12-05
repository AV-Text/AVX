#include "AVXPOS32Comparator.h"
#include <stdlib.h>

uint16 AVXPOS32Comparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint32 pos = this->pos32;
	uint32 mask = (pos & writ.pos32);

	bool match = positive ? (pos == mask) : (pos != mask);
	return match ? AVXComparator::FullMatch : 0;
}

AVXPOS32Comparator::AVXPOS32Comparator(const rapidjson::Value& node) : AVXComparator(node), pos32(0)
{
	/*
	auto comparitor = feature->match_as_pos16();

	if (comparitor != nullptr)
	{
		this->pos32 = comparitor->pnpos();
	}
	*/
}
AVXPOS32Comparator::~AVXPOS32Comparator()
{
	;
}