#pragma once
#include "AVXComparator.h"

class AVXTransitionComparator : public AVXComparator
{
public:
	uint8 tran;
	AVXTransitionComparator(const rapidjson::Value& node);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXTransitionComparator();
};

