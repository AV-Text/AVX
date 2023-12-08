#pragma once

#include <avxgen.h>
#include <string>
class TFeature
{
public:
	TFeature(std::string feature) : feature(feature), hits(0)
	{
	}
	const std::string feature;
	uint64 hits;
};

