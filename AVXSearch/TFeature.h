#pragma once

#include <Serialization.h>
#include <string>
#include <IBuild.h>
class TFeature : public IBuild
{
public:
	TFeature(std::string feature, uint16 idx): feature(feature), feature_idx(idx), hits(0)
	{
		;
	}
	virtual ~TFeature()
	{
		;
	}
	const std::string feature;
	const uint16 feature_idx;
	uint64 hits;

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
	{
		builder.StartObject();

		builder.Key("feature");
		builder.String(this->feature.c_str());

		builder.Key("feature_idx");
		builder.Uint(this->feature_idx);

		builder.Key("hits");
		builder.Uint64(this->hits);

		builder.EndObject();
	}
};

