#pragma once

#include <xvmem.h>
#include <avxgen.h>
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
public:
	bool Compile();
	//const QuelleResponse* const Execute(int64 id);
	std::vector<std::string> GetErrors(int64 id);
	std::vector<std::string> GetWarnings(int64 id);
	std::vector<std::string> GetHistory(int64 id);
	std::string GetEffects(int64 id);

	const char* const CreateRendering(int64 id);
	void Release(int64 id);

	AVXStatement(char data[]);
	~AVXStatement()
	{
		delete blueprint;
	}
};

