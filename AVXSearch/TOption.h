#pragma once

#include <avxgen.h>
#include <string>
#include <TFeature.h>

class TOption
{
public:
	TOption(std::string feature)
	{
		;
	}
	const std::vector<TFeature*> any_of;
	uint64 hits;

	~TOption()
	{
		for (auto feature : this->any_of)
		{
			delete feature;
		};
	}
};