#pragma once
#include "AVXComparator.h"

class AVXDeltaComparator : public AVXComparator
{
public:
	bool delta;
	AVXDeltaComparator(const XFeature* feature);
	virtual bool compare(AVXWritten& writ);
	virtual ~AVXDeltaComparator();
};