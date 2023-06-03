#include <AVXStatement.h>

#include <AVXBlueprint.h>
#include <unordered_set>
#include <unordered_set>
#include <vector>

#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <XVMem.h>

using namespace XBlueprintBlue;
using namespace XSearchResults;

AVXStatement::AVXStatement(HANDLE pipe)
{
	this->pipe = pipe;
}

int64 AVXStatement::Compile(const char* const command)
{
	int64 time = 0;
	uint32 len = (uint32)strlen(command);
	DWORD dwWritten;
	ResultSummary zero = { 0, 0, 0, 0 };

	if (WriteFile(pipe,
		&time,
		sizeof(int64),
		&dwWritten,
		NULL))
	{
		if (WriteFile(pipe,
			&len,
			sizeof(uint32),
			&dwWritten,
			NULL))
		{
			if (WriteFile(pipe,
				command,
				len,
				&dwWritten,
				NULL))
			{
				if (ReadFile(pipe,
					&time,
					sizeof(int64),
					&dwWritten,
					NULL))
				{
					if (ReadFile(pipe,
						&len,
						sizeof(uint32),
						&dwWritten,
						NULL))
					{
						auto buffer = (uint8*)std::malloc(len);

						auto ok = ReadFile(pipe,
							buffer,
							len,
							&dwWritten,
							NULL);
						printf("Received %d bytes\n", dwWritten);

						if (ok)
						{
							AVXBlueprint blueprint(buffer);
							XBlueprint* xblue = (XBlueprint*)blueprint.getRequest();

							if (xblue->status() == XStatusEnum::XStatusEnum_COMPLETED)
							{
								blueprint.execute();
								this->statements.add(time, buffer, len, ResultType::BLUEPRINT, zero);
								//this->statements.effect(time, xblue->singleton()->response().)
							}
							else if (xblue->status() == XStatusEnum::XStatusEnum_FEEDBACK_EXPECTED)
							{
								blueprint.execute();
								uint32 size;
								auto results = blueprint.build(size);
								ResultSummary summary = { 0, 0, 0, 0 };
								this->statements.add(time, results, size, ResultType::SEARCH_RESULTS, summary);

								if (WriteFile(pipe,
									&time,
									sizeof(int64),
									&dwWritten,
									NULL))
								{
									char simulation[] = { "Found 0 matching verses in zero books" };
									len = (uint32)Strnlen(simulation, 64);
									if (WriteFile(pipe,
										&len,
										sizeof(uint32),
										&dwWritten,
										NULL))
									{
										if (WriteFile(pipe,
											simulation,
											len,
											&dwWritten,
											NULL))
										{
											;
										}
									}
								}
							}
							else if (xblue->status() == XStatusEnum::XStatusEnum_ERROR)
							{
								this->statements.add(time, buffer, len, ResultType::UNKNOWN, zero);
							}
							else // XStatusEnum::XStatusEnum_UNKNOWN or anything else
							{
								this->statements.add(time, buffer, len, ResultType::UNKNOWN, zero);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
const QuelleResponse* const AVXStatement::Execute(int64 id)
{
	return nullptr;
}
vector<string> AVXStatement::GetErrors(int64 id)
{
	vector<string> empty;

	return empty;
}
vector<string> AVXStatement::GetWarnings(int64 id)
{
	vector<string> empty;

	return empty;
}
const char* const AVXStatement::CreateRendering(int64 id)
{
	return nullptr;
}
vector<string> AVXStatement::GetHistory(int64 id)
{
	vector<string> empty;

	return empty;
}
string AVXStatement::GetEffects(int64 id)
{
	return "";
}
void AVXStatement::Release(int64 id)
{
	this->statements.release(id);
}
