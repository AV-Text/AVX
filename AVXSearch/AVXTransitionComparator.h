#pragma once
#include "AVXComparator.h"

class AVXTransitionComparator : public AVXComparator
{
public:
	const uint8 tran;
	AVXTransitionComparator(const rapidjson::GenericObject<true, rapidjson::Value>& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXTransitionComparator();
};

