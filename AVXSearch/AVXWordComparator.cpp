#include "AVXWordComparator.h"
#include <stdlib.h>

const char* AVXWordComparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;

	if (this->wkeys != nullptr)
	{
		for (int i = 0; wkeys[i]; i++)
			if (wkeys[i] == writ.wkey)
				return this->feature;
	}
	return positive ? nullptr : this->feature;
}

AVXWordComparator::AVXWordComparator(const XFeature* feature) : AVXComparator(feature), wkeys(nullptr)
{
	auto comparitor = feature->match_as_text();

	if (comparitor != nullptr)
	{
		auto keys = comparitor->wkeys();
		if (keys != nullptr)
		{
			int len = keys->size();
			this->wkeys = (uint16*)std::calloc((keys->size() + 1), sizeof(uint16)); // null terminated
			for (int i = 0; i < len; i++)
				this->wkeys[i] = (*keys)[i];
		}
	}
}
AVXWordComparator::~AVXWordComparator()
{
	if (this->wkeys != nullptr)
	{
		std::free(this->wkeys);
	}
}

