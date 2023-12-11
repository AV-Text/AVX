#pragma once
#include "AVXComparator.h"

class AVXDeltaComparator : public AVXComparator
{
public:
	const bool delta;
	AVXDeltaComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ, TMatch& match, TTag& tag);
	virtual ~AVXDeltaComparator();
};