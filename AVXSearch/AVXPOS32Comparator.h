#pragma once
#include "AVXComparator.h"

class AVXPOS32Comparator : public AVXComparator
{
public:
	uint32 pos32;
	AVXPOS32Comparator(const XFeature* feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXPOS32Comparator();
};

