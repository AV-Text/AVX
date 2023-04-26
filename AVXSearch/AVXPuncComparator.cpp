#include "AVXPuncComparator.h"
#include <stdlib.h>

bool AVXPuncComparator::compare(AVXWritten::AVXWrit& writ)
{
	return false;
}

AVXPuncComparator::AVXPuncComparator(const XFeature* feature) : AVXComparator(feature), punc(0)
{
	auto comparitor = feature->match_as_punctuation();

	if (comparitor != nullptr)
	{
		this->punc = comparitor->bits();
	}
}

AVXPuncComparator::~AVXPuncComparator()
{
	;
}