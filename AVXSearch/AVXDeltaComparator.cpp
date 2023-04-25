#include "AVXDeltaComparator.h"
#include <stdlib.h>

bool AVXDeltaComparator::compare(AVXWritten& writ)
{
	return false;
}

AVXDeltaComparator::AVXDeltaComparator(const XFeature* feature) : AVXComparator(feature), delta(false)
{
	auto comparitor = feature->match_as_delta();

	if (comparitor != nullptr)
	{
		this->delta = comparitor->differs();
	}
}

AVXDeltaComparator::~AVXDeltaComparator()
{
	;
}