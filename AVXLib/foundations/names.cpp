#include <names.h>

AVXNames* name_lookup;

AVXNames::AVXNames(const NamesContent* const data, uint32 count)
{
	auto entry = const_cast<NamesContent*>(data);
	auto last = entry + AVXNames_RecordCnt - 1;
	size_t next = 0;
	for (/**/; entry <= last; entry += next)
	{
		auto kv = std::make_pair(entry->wkey, &(entry->meanings));
		this->names.insert(kv);

		next = sizeof(uint16) + Strnlen(&(entry->meanings), 4096) + 1;
	}
}
AVXNames::~AVXNames()
{
	this->names.clear();
}
