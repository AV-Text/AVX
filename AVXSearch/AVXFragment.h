#pragma once
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <written.h>
#include <map>

class AVXComparator;

using namespace XBlueprint;

class AVXFragment
{
public:
	bool fragment;
	AVXComparator** features;

	AVXFragment(const XFragment* xfragments);

	~AVXFragment();

	bool compare(AVXWritten::AVXWrit& writ, std::map<uint32, std::tuple<const char*, const char*>>& matches);

	inline uint32 WritAsCoordinate(AVXWritten::AVXWrit& writ)
	{
		return (((uint32)writ.b) << 24) + (((uint32)writ.c) << 16) + (((uint32)writ.b) << 8) + (uint32)writ.wc;
	}
};
