#pragma once
#include "AVXComparator.h"

class AVXLemmaComparator : public AVXComparator
{
public:
	uint16* lemmata;
	AVXLemmaComparator(const XFeature* feature);
	virtual bool compare(AVXWritten& writ);
	virtual ~AVXLemmaComparator();
};

