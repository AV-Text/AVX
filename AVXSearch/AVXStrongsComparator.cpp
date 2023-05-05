#include "AVXStrongsComparator.h"
#include <stdlib.h>

const char* AVXStrongsComparator::compare(const WrittenContent& writ)
{
	if (writ.b <= 39 && this->lang != XLangEnum_H)
		return nullptr;
	if (writ.b  > 39 && this->lang == XLangEnum_G)
		return nullptr;

	bool positive = !this->negate;
	uint16 strongs = this->number;

	for (int i = 0; i < 4; i++)
	{
		if (positive && (strongs == (writ.strongs[i] && 0x7FFF)))
			return this->feature;
	}
	return positive ? nullptr : this->feature;
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