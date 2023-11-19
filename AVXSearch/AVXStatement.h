#pragma once

#include <xvmem.h>
#include <avxgen.h>
#include <avx_search_generated.h>
#include <AVXBlueprint.h>
#include <AVXResult.h>
#include <vector>
#include <string>
#include <directory.h>
#include <lexicon.h>

class AVXStatement
{
private:
	AVXBlueprint* blueprint;
	AVXResult results;
	uint64 context;
public:
	bool Compile();
	//const QuelleResponse* const Execute(int64 id);
	vector<string> GetErrors(int64 id);
	vector<string> GetWarnings(int64 id);
	vector<string> GetHistory(int64 id);
	string GetEffects(int64 id);

	const char* const CreateRendering(int64 id);
	void Release(int64 id);

	AVXStatement(const uint8* const);
	~AVXStatement()
	{
		delete blueprint;
	}
};

