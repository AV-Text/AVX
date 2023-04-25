#pragma once
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
class AVXComparator;

using namespace Blueprint::Request;

class AVXFragment
{
public:
	const char* fragment;
	AVXComparator** features;

	AVXFragment(const XFragment* xfragments);

	~AVXFragment();
};
