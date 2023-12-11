#pragma once
#include "AVXComparator.h"

class AVXPOS32Comparator : public AVXComparator
{
public:
	const uint32 pos32;
	AVXPOS32Comparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ, TMatch& match, TTag& tag);
	virtual ~AVXPOS32Comparator();
};

