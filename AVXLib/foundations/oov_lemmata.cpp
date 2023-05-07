#include <oov_lemmata.h>

AVXLemmaOOV* lemmata_oov;

AVXLemmaOOV::AVXLemmaOOV(const OOVContent* const data, uint32 count)
{
	auto entry = const_cast<OOVContent*>(data);
	auto last = entry + AXVLemmaOOV_RecordCnt - 1;
	size_t next = 0;
	for (/**/; entry <= last; entry += next)
	{
		auto kv = std::make_pair(entry->oov_key, &(entry->oov_word));
		this->oov.insert(kv);

		next = sizeof(uint16) + Strnlen(&(entry->oov_word), 24) + 1;
	}
}
AVXLemmaOOV::~AVXLemmaOOV()
{
	this->oov.clear();
}
