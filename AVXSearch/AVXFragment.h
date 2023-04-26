#pragma once
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <written.h>
class AVXComparator;

using namespace XBlueprint;

class AVXFragment
{
public:
	const char* fragment;
	AVXComparator** features;

	AVXFragment(const XFragment* xfragments);

	~AVXFragment();

	bool compare(AVXWritten::AVXWrit& writ);
};
