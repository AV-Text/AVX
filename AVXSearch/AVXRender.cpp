#include "AVXRender.h"
#include <unordered_set>

using namespace XBlueprintBlue;

static std::unordered_set<uintptr_t> MemoryTable;


static char* internal_create_rendering(const XBlueprint& request)
{
	return nullptr;	// to do: this will be html, json, etc ....
}

// Do we need header defines for these?
extern "C" const char* const avx_create_rendering(const uint8* const data)
{
	return nullptr;
}
extern "C" bool avx_delete_rendering(const char* const rendering)
{
	auto entry = reinterpret_cast<uintptr_t>(rendering);
	auto memory = reinterpret_cast<void*>(entry);

	auto it = MemoryTable.find(entry);
	if (it != MemoryTable.end()) {
		MemoryTable.erase(it);
		free(memory);
		return true;
	}
	return false;
}
