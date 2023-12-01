#include "AVXLemmaComparator.h"
#include <stdlib.h>

// TODO: TO DO:
// If lemmata matches handle fuzziness, and settings indicate that type of search,
// then private methods on this class can handle the delegaton to the proper method
// for match logic
//
uint16 AVXLemmaComparator::compare(const WrittenContent& writ)
{
	bool positive = !this->negate;

	if (this->lemmata != nullptr)
	{
		for (int i = 0; lemmata[i]; i++)
			if (positive && (lemmata[i] == writ.lemma))
				return AVXComparator::FullMatch;
	}
	return positive ? 0 : AVXComparator::FullMatch;
}

AVXLemmaComparator::AVXLemmaComparator(ryml::ConstNodeRef feature) : AVXComparator(feature), lemmata(nullptr)
{
	if (feature != nullptr)
	{
		auto comparator = "foo-lemma"; // feature->match_as_lemma();

		if (comparator != nullptr)
		{
			/*
			auto lemmata = comparator->lemmata();

			if (lemmata != nullptr)
			{
				int len = lemmata->size();
				this->lemmata = (uint16*)std::calloc((lemmata->size() + 1), sizeof(uint16)); // null terminated
				for (int i = 0; i < len; i++)
					;//this->lemmata[i] = lemmata[i];
			}
			*/
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

