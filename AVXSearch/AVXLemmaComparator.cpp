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

	for (auto lemma : this->lemmata)
		if (positive && (lemma == writ.lemma))
			return AVXComparator::FullMatch;

	return positive ? 0 : AVXComparator::FullMatch;
}

AVXLemmaComparator::AVXLemmaComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node)
{
	if (this->node["lemmata"].IsArray())
	{
		auto array = this->node["lemmata"].GetArray();

		for (auto lemma = array.Begin(); lemma != array.End(); ++lemma)
		{
			uint16 num = lemma->GetUint();
			this->lemmata.push_back(num);
		}
	}
}

AVXLemmaComparator::~AVXLemmaComparator()
{
	;
}

