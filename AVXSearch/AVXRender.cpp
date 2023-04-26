#include "AVXRender.h"
#include <unordered_set>

using namespace XBlueprint;

static std::unordered_set<uintptr_t> MemoryTable;


static char* internal_create_rendering(const XRequest& request)
{
	return nullptr;	// to do: this will be html, json, etc ....
}

// For use with LoadLibrary/GetProcAdress ... no header file required
extern "C" __declspec(dllexport) const char* const avx_create_rendering(const uint8* const data)
{
	return nullptr;
}
extern "C" __declspec(dllexport) bool avx_delete_rendering(const char* const rendering)
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
