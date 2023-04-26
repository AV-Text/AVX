#pragma once
#include "AVXComparator.h"

class AVXPOS16Comparator : public AVXComparator
{
public:
	uint16 pos16;
	AVXPOS16Comparator(const XFeature* feature);
	virtual bool compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXPOS16Comparator();
};

