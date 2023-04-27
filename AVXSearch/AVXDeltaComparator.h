#pragma once
#include "AVXComparator.h"

class AVXDeltaComparator : public AVXComparator
{
public:
	bool delta;
	AVXDeltaComparator(const XFeature* feature);
	virtual const char* compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXDeltaComparator();
};