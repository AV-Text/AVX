#pragma once
#include "AVXComparator.h"

class AVXStrongsComparator : public AVXComparator
{
public: 
	XLangEnum lang;
	uint16 number;
	AVXStrongsComparator(const XFeature* feature);
	virtual const char* compare(AVXWritten::AVXWrit& writ);
	virtual ~AVXStrongsComparator();
};
