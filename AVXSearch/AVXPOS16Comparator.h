#pragma once
#include "AVXComparator.h"

class AVXPOS16Comparator : public AVXComparator
{
public:
	uint16 pos16;
	AVXPOS16Comparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXPOS16Comparator();
};

