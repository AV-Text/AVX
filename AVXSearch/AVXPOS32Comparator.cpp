#include "AVXPOS32Comparator.h"
#include <stdlib.h>

const char* AVXPOS32Comparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint32 pos = this->pos32;
	uint32 mask = (pos & writ.pos32);

	bool match = positive ? (pos == mask) : (pos != mask);
	return match ? this->feature : nullptr;
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