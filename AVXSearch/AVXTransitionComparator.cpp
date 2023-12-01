#include "AVXTransitionComparator.h"
#include <stdlib.h>

uint16 AVXTransitionComparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;
	uint8 tran = this->tran;
	uint8 mask = (tran & writ.tran);

	bool match = positive ? (tran == mask) : (tran != mask);
	return match ? AVXComparator::FullMatch : 0;
}

AVXTransitionComparator::AVXTransitionComparator(ryml::ConstNodeRef feature) : AVXComparator(feature), tran(0)
{
	/*
	auto comparitor = feature->match_as_punctuation();

	if (comparitor != nullptr)
	{
		this->tran = comparitor->bits();
	}
	*/
}

AVXTransitionComparator::~AVXTransitionComparator()
{
	;
}