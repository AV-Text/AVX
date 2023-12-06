#pragma once
#include "AVXComparator.h"

class AVXLemmaComparator : public AVXComparator
{
public:
	std::vector<uint16> lemmata;
	AVXLemmaComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXLemmaComparator();
};

