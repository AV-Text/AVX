#pragma once
#include "AVXComparator.h"

class AVXTransitionComparator : public AVXComparator
{
public:
	uint8 tran;
	AVXTransitionComparator(ryml::ConstNodeRef feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXTransitionComparator();
};

