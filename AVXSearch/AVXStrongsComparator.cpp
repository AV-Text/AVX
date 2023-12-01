#include "AVXStrongsComparator.h"
#include <stdlib.h>

uint16 AVXStrongsComparator::compare(const WrittenContent& writ)
{
	if (writ.b <= 39 && this->lang != 'H')
		return 0;
	if (writ.b  > 39 && this->lang == 'G')
		return 0;

	bool positive = !this->negate;
	uint16 strongs = this->number;

	for (int i = 0; i < 4; i++)
	{
		if (positive && (strongs == (writ.strongs[i] && 0x7FFF)))
			return AVXComparator::FullMatch;
	}
	return positive ? 0 : AVXComparator::FullMatch;
}

AVXStrongsComparator::AVXStrongsComparator(ryml::ConstNodeRef feature) : AVXComparator(feature), number(0), lang('X')
{
	/*
	auto comparitor = feature->match_as_strongs();

	if (comparitor != nullptr)
	{
		this->number = comparitor->number();
		this->lang = comparitor->lang();
	}
	*/
}
AVXStrongsComparator::~AVXStrongsComparator()
{
	;
}