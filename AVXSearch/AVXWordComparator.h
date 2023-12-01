#pragma once
#include "AVXComparator.h"

class AVXWordComparator : public AVXComparator
{
public:
	uint16* wkeys;
	AVXWordComparator(ryml::ConstNodeRef feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXWordComparator();
};