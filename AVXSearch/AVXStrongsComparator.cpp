#include "AVXStrongsComparator.h"
#include <stdlib.h>

bool AVXStrongsComparator::compare(AVXWritten& writ)
{
	return false;
}

AVXStrongsComparator::AVXStrongsComparator(const XFeature* feature) : AVXComparator(feature), number(0), lang(XLangEnum_MIN)
{
	auto comparitor = feature->match_as_strongs();

	if (comparitor != nullptr)
	{
		this->number = comparitor->number();
		this->lang = comparitor->lang();
	}
}
AVXStrongsComparator::~AVXStrongsComparator()
{
	;
}