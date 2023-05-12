// PipeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <fileapi.h>

#include <AVXBlueprint.h>
#include <unordered_set>
#include <unordered_set>
#include <vector>

#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprintBlue;
using namespace XSearchResults;

#define PIPE_NAME "\\\\.\\pipe\\Blueprint-Blue-Service"

#include <iostream>
#include <string>

#include <directory.h>

#define DEFAULT_BUFFER_MAX 4*1024
int main()
{
	HANDLE hPipe;
	DWORD dwWritten;
	uint8 defaultBuffer[DEFAULT_BUFFER_MAX];

	hPipe = CreateFile(PIPE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		directory omega("C:\\src\\AVX\\omega\\AVX-Omega-3507.data");

		std::string line;

	restart:
		std::printf("> ");
		std::getline(std::cin, line);

		if (!line.empty())
		{
			auto msg = line.c_str();

			int64 time = 0;
			uint32 len = (uint32)strlen(msg);

			if (WriteFile(hPipe,
				&time,
				sizeof(int64),
				&dwWritten,
				NULL))
			{
				if (WriteFile(hPipe,
					&len,
					sizeof(uint32),
					&dwWritten,
					NULL))
				{
					if (WriteFile(hPipe,
						msg,
						len,
						&dwWritten,
						NULL))
					{
						if (ReadFile(hPipe,
							&time,
							sizeof(int64),
							&dwWritten,
							NULL))
						{
							if (ReadFile(hPipe,
								&len,
								sizeof(uint32),
								&dwWritten,
								NULL))
							{
								auto buffer = len <= DEFAULT_BUFFER_MAX ? defaultBuffer : (uint8*)std::malloc(len);

								auto ok = ReadFile(hPipe,
									buffer,
									len,
									&dwWritten,
									NULL);
								printf("Received %d bytes\n", dwWritten);

								if (ok)
								{
									AVXBlueprint blueprint(buffer);
									XBlueprint* xblue = (XBlueprint*)blueprint.getRequest();

									if (xblue->status() == XStatusEnum::XStatusEnum_ACTION_REQUIRED)
									{
										blueprint.execute();
									}
									else if (xblue->status() == XStatusEnum::XStatusEnum_FEEDBACK_EXPECTED)
									{
										blueprint.execute();
										auto results = blueprint.build();

										if (WriteFile(hPipe,
											&time,
											sizeof(int64),
											&dwWritten,
											NULL))
										{
											char simulation[] = { "Found 0 matching verses in zero books" };
											len = (uint32)Strnlen(simulation, 64);
											if (WriteFile(hPipe,
												&len,
												sizeof(uint32),
												&dwWritten,
												NULL))
											{
												if (WriteFile(hPipe,
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
										;
									}
									else // XStatusEnum::XStatusEnum_UNKNOWN or anything else
									{
										;
									}
								}
								if (buffer != defaultBuffer)
								{
									free((void*)buffer);
								}
							}
						}
					}
				}
			}
			goto restart;
		}
		CloseHandle(hPipe);
	}

	return 0;
}