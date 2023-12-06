#include "AVXPOS16Comparator.h"
#include <stdlib.h>

uint16 AVXPOS16Comparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint16 pos = this->pos16;
	uint16 mask = (pos & writ.pn_pos12);

	bool match = positive ? (pos == mask) : (pos != mask);
	return match ? AVXComparator::FullMatch : 0;
}

AVXPOS16Comparator::AVXPOS16Comparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node), pos16(node["pnpos"].GetUint())
{
	;
}

AVXPOS16Comparator::~AVXPOS16Comparator()
{
	;
}