#pragma once
#include "AVXComparator.h"

class AVXStrongsComparator : public AVXComparator
{
public: 
	XLangEnum lang;
	uint16 number;
	AVXStrongsComparator(const XFeature* feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXStrongsComparator();
};

