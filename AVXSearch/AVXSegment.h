#pragma once
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <map>

using namespace XBlueprint;

#include <written.h>
class AVXFragment;
class AVXSegment
{
public:
	AVXSegment(const XSegment* xsegments);

	const char* segment;
	const bool anchored;
	AVXFragment** fragments;

	//AVXSegment(const XSegment* xsegments);

	~AVXSegment();

	bool compare(AVXWritten::AVXWrit& writ, std::map<uint32, std::tuple<const char*, const char*>>& matches);
};

