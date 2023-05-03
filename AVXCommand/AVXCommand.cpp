// PipeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <fileapi.h>

#include "AVXBlueprint.h"
#include <unordered_set>
#include <book_index.h>
#include <unordered_set>
#include <vector>

#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

#define PIPE_NAME "\\\\.\\pipe\\Blueprint-Blue-Service"

#include <iostream>
#include <string>

int main()
{
	HANDLE hPipe;
	DWORD dwWritten;
	uint8 buffer[1024];

	hPipe = CreateFile(PIPE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (hPipe != INVALID_HANDLE_VALUE)
	{
		std::string line;

	restart:
		std::getline(std::cin, line);

		if (!line.empty())
		{
			auto msg = line.c_str();

			uint32 len = (uint32)strlen(msg);

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
						&len,
						sizeof(uint32),
						&dwWritten,
						NULL))
					{
						auto ok = (len <= 1024) && ReadFile(hPipe,
							buffer,
							len,
							&dwWritten,
							NULL);
						printf("Received %d bytes\n", dwWritten);

						if (ok)
						{
							AVXBlueprint search(buffer);
							search.execute();
							auto results = search.build();
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