#pragma once

#include <DigitalAV.h>

static XVMem<const uint8*> OmegaFile;

extern "C" uint32 initialize(const char* data)
{
	OmegaFile.Acquire("AVX-Omega", data, false, true);

	return 0;
}