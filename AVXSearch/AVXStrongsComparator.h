#pragma once
#include "AVXComparator.h"

class AVXStrongsComparator : public AVXComparator
{
public: 
	char lang;
	uint16 number;
	AVXStrongsComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXStrongsComparator();
};

