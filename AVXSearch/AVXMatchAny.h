#pragma once
#include <directory.h>
#include <map>

class AVXComparator;

#include <ryml.hpp>

class AVXMatchAny
{
public:
	const char* options;
	AVXComparator** features;

	AVXMatchAny(ryml::ConstNodeRef options);

	~AVXMatchAny();

	bool compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched);

	inline uint32 WritAsCoordinate(const WrittenContent& writ)
	{
		return (((uint32)writ.b) << 24) + (((uint32)writ.c) << 16) + (((uint32)writ.b) << 8) + (uint32)writ.wc;
	}
};
