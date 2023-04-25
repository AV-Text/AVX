#include "AVXPOS32Comparator.h"
#include <stdlib.h>

bool AVXPOS32Comparator::compare(AVXWritten& writ)
{
	return false;
}

AVXPOS32Comparator::AVXPOS32Comparator(const XFeature* feature) : AVXComparator(feature), pos32(0)
{
	auto comparitor = feature->match_as_pos16();

	if (comparitor != nullptr)
	{
		this->pos32 = comparitor->pnpos();
	}
}
AVXPOS32Comparator::~AVXPOS32Comparator()
{
	;
}