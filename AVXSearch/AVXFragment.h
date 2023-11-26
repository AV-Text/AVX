#pragma once
#include <blueprint_blue_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <map>

using namespace XBlueprintBlue;

#include <directory.h>
class AVXMatchAny;
class AVXFragment
{
public:
	AVXFragment(const XFragment* xfragments);

	const char* fragment;
	const bool anchored;
	AVXMatchAny** requirements;

	~AVXFragment();

	bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);
};

