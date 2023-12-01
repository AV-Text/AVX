#include "AVXPuncComparator.h"
#include <stdlib.h>

uint16 AVXPuncComparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint8 punc = this->punc;
	uint8 mask = (punc & writ.punc);

	bool match = positive ? (punc == mask) : (punc != mask);
	return match ? AVXComparator::FullMatch : 0;
}

AVXPuncComparator::AVXPuncComparator(ryml::ConstNodeRef feature) : AVXComparator(feature), punc(0)
{
	/*
	auto comparitor = feature->match_as_punctuation();

	if (comparitor != nullptr)
	{
		this->punc = comparitor->bits();
	}
	*/
}

AVXPuncComparator::~AVXPuncComparator()
{
	;
}