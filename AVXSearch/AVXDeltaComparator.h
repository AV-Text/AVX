#pragma once
#include "AVXComparator.h"

class AVXDeltaComparator : public AVXComparator
{
public:
	bool delta;
	AVXDeltaComparator(const XFeature* feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXDeltaComparator();
};