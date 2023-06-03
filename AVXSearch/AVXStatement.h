#pragma once

#include <xvmem.h>
#include <avxgen.h>
#include <fileapi.h>
#include <QuelleResponse.h>
#include <vector>
#include <string>

// this will be the external public interface into this library
//
#define DEFAULT_BUFFER_MAX 4*1024

class AVXStatement
{
private:
	CommandResponses statements;
	HANDLE pipe;
public:
	int64 Compile(const char* const command); // return statement_id
	const QuelleResponse* const Execute(int64 id);
	vector<string> GetErrors(int64 id);
	vector<string> GetWarnings(int64 id);
	vector<string> GetHistory(int64 id);
	string GetEffects(int64 id);

	const char* const CreateRendering(int64 id);
	void Release(int64 id);

	AVXStatement(HANDLE pipe);
};

