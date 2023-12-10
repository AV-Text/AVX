#pragma once

#include <Serialization.h>
#include <string>
#include <IBuild.h>
#include<AVXComparator.h>

class TFeature : public IBuild
{
public:
	TFeature(AVXComparator& comparator, uint16 idx): feature(comparator.feature), feature_idx(idx), feature_avx(comparator), hits(0)
	{
		;
	}
	virtual ~TFeature()
	{
		;
	}
	const std::string feature;
	const uint16 feature_idx;
	AVXComparator& feature_avx;
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

