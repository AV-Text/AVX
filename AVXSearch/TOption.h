#pragma once

#include <avxgen.h>
#include <string>
#include <vector>
#include <TFeature.h>
#include <AVXMatchAny.h>
#include <AVXComparator.h>

class AVXComparator;
class TOption
{
public:
	TOption(AVXMatchAny& option)
	{
		for (auto feature : option.features)
		{
			//this->any_of.push_back(new TFeature(feature->feature));
		}
	}
	const std::vector<TFeature*> any_of;
	uint64 hits;

	~TOption()
	{
		for (auto feature : this->any_of)
		{
			delete feature;
		}
	}
};