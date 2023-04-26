#pragma once
#include "AVXComparator.h"

class AVXWordComparator : public AVXComparator
{
public:
	uint16* wkeys;
	AVXWordComparator(const XFeature* feature);
	virtual bool compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXWordComparator();
};