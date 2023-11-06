#include <lemmata.h>

AVXLemmata* lemmata_lookup;

AVXLemmata::AVXLemmata(const LemmataContent* const data, uint32 count)
{
	auto entry = const_cast<LemmataContent*>(data);
	auto last = entry + AVXLemmata_RecordCnt - 1;
	size_t next = 0;
	uint16* array = nullptr;
	for (/**/; entry <= last; entry = (LemmataContent*)(array + entry->lemma_count))
	{
		uint64 key = (((uint64)entry->pos32) << 32) + (((uint64)entry->pn_pos12) << 16) + entry->wkey;
		auto kv = std::make_pair(key, entry);
		this->lemmata.insert(kv);

		array = &(entry->lemmata);
	}
}
AVXLemmata::~AVXLemmata()
{
	this->lemmata.clear();
}