#pragma once
#include "AVXComparator.h"

class AVXWordComparator : public AVXComparator
{
public:
	uint16* wkeys;
	AVXWordComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXWordComparator();
};