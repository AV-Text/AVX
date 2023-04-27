#pragma once
#include "AVXComparator.h"

class AVXTransitionComparator : public AVXComparator
{
public:
	uint8 tran;
	AVXTransitionComparator(const XFeature* feature);
	virtual const char* compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXTransitionComparator();
};

