#pragma once
#include "AVXComparator.h"

class AVXPOS32Comparator : public AVXComparator
{
public:
	uint32 pos32;
	AVXPOS32Comparator(const XFeature* feature);
	virtual const char* compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXPOS32Comparator();
};
