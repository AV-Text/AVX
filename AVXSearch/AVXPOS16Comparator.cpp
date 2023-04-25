#include "AVXPOS16Comparator.h"
#include <stdlib.h>

bool AVXPOS16Comparator::compare(AVXWritten& writ)
{
	return false;
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