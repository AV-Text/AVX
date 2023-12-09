#pragma once

#include <Serialization.h>
#include <string>
#include <IBuild.h>
class TFeature : public IBuild
{
public:
	TFeature(std::string feature): feature(feature), hits(0)
	{
		;
	}
	virtual ~TFeature()
	{
		;
	}
	const std::string feature;
	uint64 hits;

	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
	{
		builder.StartObject();

		builder.Key("feature");
		builder.String(this->feature.c_str());

		builder.Key("hits");
		builder.Uint64(this->hits);

		builder.EndObject();
	}
};

