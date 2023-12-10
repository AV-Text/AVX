#pragma once

#include <Serialization.h>
#include <string>
#include <vector>
#include <IBuild.h>
#include <TFeature.h>
#include <AVXMatchAny.h>
#include <AVXComparator.h>

class AVXComparator;
class TOptions : public IBuild
{
public:
	TOptions(AVXMatchAny& match_any, uint16 match_any_idx): options_avx(match_any)
	{
		this->options = match_any.options;
		this->options_idx = match_any_idx;
		uint16 idx = 0;
		for (auto feature : match_any.features)
		{
			this->any_of.push_back(new TFeature(*feature, idx++));
		}
	}
	std::vector<TFeature*> any_of;
	std::string options;
	uint16 options_idx;
	AVXMatchAny& options_avx;
	uint64 hits;

	virtual ~TOptions()
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

		builder.Key("options");
		builder.String(this->options.c_str());

		builder.Key("options_idx");
		builder.Uint(this->options_idx);

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