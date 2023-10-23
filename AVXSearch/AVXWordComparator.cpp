#include "AVXWordComparator.h"
#include <stdlib.h>

// TODO: TO DO:
// This needs to handle fuzziness, when settings indicate that type of search:
// private methods on this class can handle the delegaton to the proper method
// for match logic
//
uint16 AVXWordComparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;

	if (this->wkeys != nullptr)
	{
		for (int i = 0; wkeys[i]; i++)
			if (wkeys[i] == writ.wkey)
				return AVXComparator::FullMatch;
	}
	return positive ? 0 : this->AVXComparator::FullMatch;
}

AVXWordComparator::AVXWordComparator(const XFeature* feature) : AVXComparator(feature), wkeys(nullptr)
{
	if (feature != nullptr)
	{
		auto comparator = feature->match_as_text();

		if (comparator != nullptr)
		{
			auto keys = comparator->lex();

			if (keys != nullptr)
			{
				int len = keys->size();
				this->wkeys = (uint16*)std::calloc((keys->size() + 1), sizeof(uint16)); // null terminated
				for (int i = 0; i < len; i++)
					;// this->wkeys[i] = (*keys)[i];
			}
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

