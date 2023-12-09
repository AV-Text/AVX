#pragma once

#include <Serialization.h>
#include <string>
#include <vector>
#include <IBuild.h>
#include <TFeature.h>
#include <AVXMatchAny.h>
#include <AVXComparator.h>

class AVXComparator;
class TOption : public IBuild
{
public:
	TOption(AVXMatchAny& option)
	{
		for (auto feature : option.features)
		{
			this->any_of.push_back(new TFeature(feature->feature));
		}
	}
	std::vector<TFeature*> any_of;
	uint64 hits;

	virtual ~TOption()
	{
		for (auto feature : this->any_of)
		{
			delete feature;
		}
	}
	
	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
	{
		builder.StartObject();

		builder.Key("hits");
		builder.Uint64(this->hits);

		builder.Key("any_of");
		builder.StartArray();
		for (auto feature : this->any_of)
		{
			feature->build(builder);
		}
		builder.EndArray();

		builder.EndObject();
	}
};