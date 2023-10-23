#pragma once
#include <blueprint_blue_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <map>

using namespace XBlueprintBlue;

#include <directory.h>
class AVXFragment;
class AVXSegment
{
public:
	AVXSegment(const XSegment* xsegments);

	const char* segment;
	const bool anchored;
	AVXFragment** fragments;

	~AVXSegment();

	bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);
};

