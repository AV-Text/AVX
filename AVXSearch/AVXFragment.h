#pragma once
#include <map>
#include <string>
#include <vector>
#include <directory.h>
#include <Deserialization.h>

class AVXMatchAny;
class AVXFragment
{
public:
	AVXFragment(rapidjson::GenericObject<true, rapidjson::Value>& fragment);

	const rapidjson::GenericObject<true, rapidjson::Value>& fragment;
	const bool anchored;
	std::string text;
	std::vector <AVXMatchAny*> requirements;

	~AVXFragment();

	// OBSOLETE FUNCTION (no longer used)
	// bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);

private:
	bool okay;
	std::string error;
};

