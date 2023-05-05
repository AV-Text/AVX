#pragma once
#include "AVXComparator.h"

class AVXLemmaComparator : public AVXComparator
{
public:
	uint16* lemmata;
	AVXLemmaComparator(const XFeature* feature);
	virtual const char* compare(const WrittenContent& writ);
	virtual ~AVXLemmaComparator();
};

