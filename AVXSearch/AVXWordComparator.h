#pragma once
#include "AVXComparator.h"

class AVXWordComparator : public AVXComparator
{
public:
	uint16* wkeys;
	AVXWordComparator(const XFeature* feature);
	virtual const char* compare(const WrittenContent& writ);
	virtual ~AVXWordComparator();
};