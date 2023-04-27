#include "AVXLemmaComparator.h"
#include <stdlib.h>

const char* AVXLemmaComparator::compare(AVXWritten::AVXWrit& writ)
{
	bool positive = !this->negate;

	if (this->lemmata != nullptr)
	{
		for (int i = 0; lemmata[i]; i++)
			if (positive && (lemmata[i] == writ.lemma))
				return this->feature;
	}
	return positive ? nullptr : this->feature;
}

AVXLemmaComparator::AVXLemmaComparator(const XFeature* feature) : AVXComparator(feature), lemmata(nullptr)
{
	auto comparitor = feature->match_as_text();

	if (comparitor != nullptr)
	{
		auto keys = comparitor->wkeys();
		if (keys != nullptr)
		{
			int len = keys->size();
			this->lemmata = (uint16*)std::calloc((keys->size() + 1), sizeof(uint16)); // null terminated
			for (int i = 0; i < len; i++)
				this->lemmata[i] = (*keys)[i];
		}
	}
}

AVXLemmaComparator::~AVXLemmaComparator()
{
	if (this->lemmata != nullptr)
	{
		std::free(this->lemmata);
	}
}

