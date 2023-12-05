#pragma once
#include <map>

#include <directory.h>
#include <rapidjson/document.h>

class AVXMatchAny;
class AVXFragment
{
public:
	AVXFragment(rapidjson::Value& fragments);

	const char* fragment;
	const bool anchored;
	AVXMatchAny** requirements;

	~AVXFragment();

	bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);
};

