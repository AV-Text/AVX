#pragma once
#include "AVXComparator.h"

class AVXPuncComparator : public AVXComparator
{
public:
	uint8 punc;
	AVXPuncComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXPuncComparator();
};

