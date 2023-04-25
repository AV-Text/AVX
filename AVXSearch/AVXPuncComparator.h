#pragma once
#include "AVXComparator.h"

class AVXPuncComparator : public AVXComparator
{
public:
	uint8 punc;
	AVXPuncComparator(const XFeature* feature);
	virtual bool compare(AVXWritten& writ);
	virtual ~AVXPuncComparator();
};

