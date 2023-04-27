#pragma once
#include "AVXComparator.h"

class AVXPuncComparator : public AVXComparator
{
public:
	uint8 punc;
	AVXPuncComparator(const XFeature* feature);
	virtual const char* compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXPuncComparator();
};

