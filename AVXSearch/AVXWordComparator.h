#pragma once
#include "AVXComparator.h"

class AVXWordComparator : public AVXComparator
{
public:
	std::vector<uint16> wkeys;
	AVXWordComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ, TMatch& match, TTag& tag);
	virtual ~AVXWordComparator();
};