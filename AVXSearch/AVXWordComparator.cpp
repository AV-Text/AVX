#include "AVXWordComparator.h"
#include <stdlib.h>

// TODO: TO DO:
// This needs to handle fuzziness, when settings indicate that type of search:
// private methods on this class can handle the delegaton to the proper method
// for match logic
//
uint16 AVXWordComparator::compare(const WrittenContent& writ, TMatch& match, TTag& tag)
{
	bool positive = !this->negate;

	for (auto key : this->wkeys)
		if (key == (writ.wkey & 0x3FFF))
			return positive ? AVXComparator::FullMatch : 0;

	// TO DO: (TODO)
	// Fuzzy match

	return positive ? 0 : this->AVXComparator::FullMatch;
}

AVXWordComparator::AVXWordComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node)
{
	if (this->node.HasMember("WordKeys") && this->node["WordKeys"].IsArray())
	{
		auto array = this->node["WordKeys"].GetArray();

		for (auto word = array.Begin(); word != array.End(); ++word)
		{
			uint16 num = word->GetUint();
			this->wkeys.push_back(num);
		}
	}
	if (this->node.HasMember("Phonetics") && this->node["Phonetics"].IsArray())
	{
		auto array = this->node["Phonetics"].GetArray();

		for (auto item = array.Begin(); item != array.End(); ++item)
		{
			auto ipa = item->GetString();
			this->phonetics.push_back(ipa);
		}
	}
}

AVXWordComparator::~AVXWordComparator()
{
	;
}

