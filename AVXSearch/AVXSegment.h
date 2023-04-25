#pragma once
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace Blueprint::Request;

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
};

