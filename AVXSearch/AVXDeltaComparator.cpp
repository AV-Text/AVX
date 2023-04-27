#include "AVXDeltaComparator.h"
#include <stdlib.h>

const char* AVXDeltaComparator::compare(AVXWritten::AVXWrit& writ)
{
	return nullptr; // TODO: I need to load the lexicon for this one
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