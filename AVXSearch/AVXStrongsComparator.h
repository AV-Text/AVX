#pragma once
#include "AVXComparator.h"

class AVXStrongsComparator : public AVXComparator
{
public: 
	std::string lang;
	const uint16 number;
	AVXStrongsComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ, TMatch& match, TTag& tag);
	virtual ~AVXStrongsComparator();
};

