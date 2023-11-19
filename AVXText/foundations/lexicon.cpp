#include <lexicon.h>

AVXLexTokenMap LexLookup;
AVXLexKeyMap   LexMap;

bool AVXLexTokenMap::create_lexicon(const LexiconContent* const lex, uint32 count, bool createLexicalLookupMap)
{
	auto entry = const_cast<LexiconContent*>(lex);
	auto last = entry + count - 1;

	for (uint16 key = 0; entry <= last; key++)
	{
		LexMap.add(key, *entry);
		if (createLexicalLookupMap)
			LexLookup.add(key, *entry);

		size_t len = (sizeof(uint16) * 2) + (sizeof(uint32) * entry->size);

		char* strings = ((char*)entry) + len;
		for (int i = 0; i < 3; i++)
		{
			auto str_len = Strnlen(strings, 24) + 1;
			strings += str_len;
		}
		entry = (LexiconContent*) strings;
	}
	return (count > 0);
}

bool AVXLexTokenMap::delete_lexicon()
{
	return LexLookup.clear_lexicon();
}

bool AVXLexTokenMap::clear_lexicon()
{
	this->kjv.clear();
	this->mod.clear();

	return true;
}

int AVXLexTokenMap::add(const uint16 key, const LexiconContent& lex)
{
	std::string search(NormalizeDisplay(lex));
	std::string modern(NormalizeModern(lex));

	auto kvsearch = std::make_pair(search, (uint16)key);
	this->kjv.insert(kvsearch);
	int cnt = 1;

	auto existing = this->GetExistingModernVector(modern);
	if (existing != nullptr)
	{
		cnt += int(existing->size() + 1);
		existing->push_back(key);
	}
	else
	{
		cnt++;
		std::vector<uint16> added;
		added.push_back(key);
		auto kvmodern = std::make_pair(modern, added);
		this->mod.insert(kvmodern);
	}
	return cnt; // 1, 2, or 3
}
