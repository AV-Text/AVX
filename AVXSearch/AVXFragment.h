#pragma once
#include <blueprint_blue_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <directory.h>
#include <map>

class AVXComparator;

using namespace XBlueprintBlue;

class AVXFragment
{
public:
	bool fragment;
	AVXComparator** features;

	AVXFragment(const XFragment* xfragments);

	~AVXFragment();

	bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const char*>>& matched);

	inline uint32 WritAsCoordinate(const WrittenContent& writ)
	{
		return (((uint32)writ.b) << 24) + (((uint32)writ.c) << 16) + (((uint32)writ.b) << 8) + (uint32)writ.wc;
	}
};
