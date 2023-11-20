// PipeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// The Named-Pipe communication eventually needs to be moved into AVX-Search
//
// extern "C" functions will be defined as follows:
/*
	int Execute(ref int summarySize, ref in resultsSize): return value is int64 timestamp [or zero when action is complete]
	int GetSummary(int timestamp, uint8* buffer, uint32 bufferSize): return value is ftatbuffer-defined enum for status
	const char* CreateRendering(int timestamp, uint8* buffer, uint32 bufferSize): buffer
	const char* FreeRendering(int timestamp, uint8* buffer, uint32 bufferSize): buffer
	int GetHistory(int64 notBefore, int64 notAfter, const char* buffer, uint32 size): returns size required to hold content (or zero when size provided was sufficient)
	int ExecuteSingleton(char* effect, in effectSize): return value is status
 */

#include <windows.h>
//#include <fileapi.h>

//#include <AVXBlueprint.h>
#include <unordered_set>
#include <unordered_set>
#include <vector>

#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprintBlue;
using namespace XSearchResults;

#include <iostream>
#include <string>

//#include <directory.h>

//#include <AVXStatement.h>

#define DEFAULT_BUFFER_MAX 4*1024

extern "C" __declspec(dllimport) uint64_t create_avxtext(const char* data);
//extern "C" __declspec(dllimport) void free_avxtext(uint64_t data);

int main()
{
	auto sdk = create_avxtext("C:/src/AVX/omega/AVX-Omega-3911.data");
	std::string line;

restart:
	std::printf("> ");
	std::getline(std::cin, line);

	if (!line.empty())
	{
//		auto id = stmt.Compile(msg);

		goto restart;
	}
//	free_avxtext(sdk);
	return 0;
}