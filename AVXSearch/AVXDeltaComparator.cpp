#include "AVXDeltaComparator.h"
#include <stdlib.h>
#include <directory.h>
#include <lexicon.h>

uint16 AVXDeltaComparator::compare(const WrittenContent& writ)
{
	if (directory::GLOBAL != nullptr && directory::GLOBAL->isOkay())
	{
		auto entry = LexMap.get(writ.wkey);
		if (entry != nullptr)
		{
			return CanBeModernized(*entry);
		}
	}
	return false;
}

AVXDeltaComparator::AVXDeltaComparator(ryml::ConstNodeRef feature) : AVXComparator(feature), delta(false)
{
	/*
	auto comparitor = feature->match_as_delta();

	if (comparitor != nullptr)
	{
		this->delta = comparitor->differs();
	}
	*/
}

AVXDeltaComparator::~AVXDeltaComparator()
{
	;
}