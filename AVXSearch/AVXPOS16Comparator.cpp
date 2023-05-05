#include "AVXPOS16Comparator.h"
#include <stdlib.h>

const char* AVXPOS16Comparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint16 pos = this->pos16;
	uint16 mask = (pos & writ.pn_pos12);

	bool match = positive ? (pos == mask) : (pos != mask);
	return match ? this->feature : nullptr;
}

AVXPOS16Comparator::AVXPOS16Comparator(const XFeature* feature) : AVXComparator(feature), pos16(0)
{
	auto comparitor = feature->match_as_pos16();

	if (comparitor != nullptr)
	{
		this->pos16 = comparitor->pnpos();
	}
}

AVXPOS16Comparator::~AVXPOS16Comparator()
{
	;
}