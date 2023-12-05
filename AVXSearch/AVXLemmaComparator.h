#pragma once
#include "AVXComparator.h"

class AVXLemmaComparator : public AVXComparator
{
public:
	uint16* lemmata;
	AVXLemmaComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXLemmaComparator();
};

