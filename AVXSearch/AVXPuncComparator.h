#pragma once
#include "AVXComparator.h"

class AVXPuncComparator : public AVXComparator
{
public:
	const uint8 punc;
	AVXPuncComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXPuncComparator();
};

