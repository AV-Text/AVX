#pragma once
#include <directory.h>
#include <map>
#include <vector>
#include <string>

class AVXComparator;

#include <rapidjson/document.h>

class AVXMatchAny
{
public:
	const char* options;
	std::vector <AVXComparator*> features;

	AVXMatchAny(rapidjson::GenericObject<true, rapidjson::Value>& opts);

	~AVXMatchAny();

	// OBSOLETE FUNCTION (no longer used)
	// bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);

	inline uint32 WritAsCoordinate(const WrittenContent& writ)
	{
		return (((uint32)writ.b) << 24) + (((uint32)writ.c) << 16) + (((uint32)writ.b) << 8) + (uint32)writ.wc;
	}
private:
	rapidjson::GenericObject<true, rapidjson::Value>& matchany;
	bool okay;
	std::string error;
};
