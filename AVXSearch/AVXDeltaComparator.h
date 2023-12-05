#pragma once
#include "AVXComparator.h"

class AVXDeltaComparator : public AVXComparator
{
public:
	bool delta;
	AVXDeltaComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXDeltaComparator();
};