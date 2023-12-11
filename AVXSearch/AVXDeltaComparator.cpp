#include "AVXDeltaComparator.h"
#include <stdlib.h>
#include <directory.h>
#include <lexicon.h>

uint16 AVXDeltaComparator::compare(const WrittenContent& writ, TMatch& match, TTag& tag)
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

AVXDeltaComparator::AVXDeltaComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node), delta(node["delta"].GetBool())
{
	;
}

AVXDeltaComparator::~AVXDeltaComparator()
{
	;
}