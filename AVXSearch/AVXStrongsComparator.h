#pragma once
#include "AVXComparator.h"

class AVXStrongsComparator : public AVXComparator
{
public: 
	char lang;
	uint16 number;
	AVXStrongsComparator(ryml::ConstNodeRef feature);
	virtual uint16 compare(const WrittenContent& writ);
	virtual ~AVXStrongsComparator();
};

