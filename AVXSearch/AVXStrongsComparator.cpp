#include "AVXStrongsComparator.h"
#include <stdlib.h>

uint16 AVXStrongsComparator::compare(const WrittenContent& writ, TMatch& match, TTag& tag)
{
	char code = this->lang.length() == 1 ? this->lang[0] : 'X';

	if (writ.b <= 39 && code != 'H')
		return 0;
	if (writ.b  > 39 && code != 'G')
		return 0;

	bool positive = !this->negate;
	uint16 num = this->number;

	for (int i = 0; i < 4; i++)
	{
		if (positive && (num == (writ.strongs[i] & 0x7FFF)))
			return AVXComparator::FullMatch;
	}
	return positive ? 0 : AVXComparator::FullMatch;
}

AVXStrongsComparator::AVXStrongsComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node) : AVXComparator(node), number(node["number"].GetUint()), lang(node["pos32"].GetString())
{
	;
}
AVXStrongsComparator::~AVXStrongsComparator()
{
	;
}