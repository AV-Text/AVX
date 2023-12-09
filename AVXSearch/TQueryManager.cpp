///////////////////////////////////////////////////////////
//  TQueryManager.cpp
//  Implementation of the Class TQueryManager
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TQueryManager.h"
#include "AVXFragment.h"
#include "AVXBlueprint.h"
#include "AVXFind.h"
#include <TMatch.h>
#include <TTag.h>
#include <map>
#include <directory.h>
#include <book.h>

TQueryManager::TQueryManager(){

}

TQueryManager::~TQueryManager(){

}

TQuery * TQueryManager::create(AVXBlueprint* blueprint)
{
	auto query = new TQuery(blueprint);
	auto query_id = uint64(query);
	this->queries[query_id] = query; // we don't really need a map for this, but it is the current design

	return query;
}

bool TQueryManager::add_scope(uint64 query_id, byte book, byte chapter, byte verse_from, byte verse_to)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];

        uint32 verse_range = 0;
        if (verse_from != 0)
        {
            verse_range = uint32(verse_from) << 24 + uint32(verse_to) << 16;
        }
		query->scope.push_back(uint32(book) << 16 | uint32(chapter) << 8 | verse_range);
		return true;
	}
	return false;
}

std::string TQueryManager::fetch(uint64 query_id)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		return query->serialize();
	}
    return "";
}

// returns tree for map<byte, TChapter>
std::string TQueryManager::fetch(uint64 query_id, byte book, byte chapter)
{
	auto iquery = this->queries.find(query_id);
	if (iquery != this->queries.end())
	{
		TQuery* query = this->queries[query_id];
		if (book >= 1 && book <= 66 && query->books[book-1] != nullptr)
		{
			auto result = query->fetch(book, chapter);

            return result;
		}
	}
    return "";
}

bool TQueryManager::search_quoted(TQuery& query, AVXFind& segment)
{
    auto frag_cnt = segment.fragments.size();

    if (frag_cnt < 1)
        return false;

    bool hit = false;
    for (uint8 b = 1; b <= 66; b++)
    {
        auto book = AVXBook::GetBook(b);
        auto writ = book.getWrit();

        uint32 w;

        if (query.settings.span > 0)
        {
            uint32 len = 0;
            for (w = 0; w < book.writ_cnt; w++, writ++)
            {
                if (len == 0)
                {
                    len = w + query.settings.span;
                    if (len > book.writ_cnt)
                        len = book.writ_cnt;
                }
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                bool found = false; // obsolete from AVXFound: this->requirements[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    auto spanwrit = writ + 1;

                    for (auto fragment : segment.fragments)
                    {
                        ;
                    }/*
                    for (uint32 seg_idx = 1; this->requirements[seg_idx]; seg_idx++)
                    {
                        for (auto& segment = *(this->requirements[seg_idx]); wi < len; wi++, spanwrit++)
                        {
                            if (!segment.compare(*spanwrit, matched))
                            {
                                if (segment.anchored)
                                    goto NOT_FOUND_1;
                                if (wi == len-1) // end-of-verse with verse-span granularity
                                    goto NOT_FOUND_1;
                            }
                        }
                    }
                    hit = true;
                    auto found = new TFound();
                    for (auto const& [coord, pair] : matched)
                    {
                        const char* frag = std::get<0>(pair);
                        const char* feat = std::get<0>(pair);
                        auto match = new TMatch((uint32) coord, frag, feat);
                        found->add(match);
                    }
                    //this->results.founds.push_back(found);
                    */
                }
            NOT_FOUND_1:
                continue;
            }
        }
        else
        {
            uint32 len = writ->wc;
            for (w = 0; w < book.writ_cnt; w += len, writ += len)
            {
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                bool found = false; // this->requirements[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    uint32 wi_len = wi + len;

                    auto spanwrit = writ + 1;

                    for (auto fragment : segment.fragments)
                    {
                        ;
                    }/*

                    for (uint32 seg_idx = 1; this->requirements[seg_idx]; seg_idx++)
                    {
                        for (auto& segment = *(this->requirements[seg_idx]); wi < wi_len; wi++, spanwrit++)
                        {
                            if (!segment.compare(*spanwrit, matched))
                            {
                                if (segment.anchored)
                                    goto NOT_FOUND_2;
                                if (wi == wi_len - 1) // end-of-verse with verse-span granularity
                                    goto NOT_FOUND_2;
                            }
                        }
                    }
                    hit = true;
                    auto found = new TFound();
                    for (auto const& [coord, pair] : matched)
                    {
                        const char* frag = std::get<0>(pair);
                        const char* feat = std::get<0>(pair);
                        auto match = new AVXMatch((uint32)coord, frag, feat);
                        found->add(match);
                    }*/
                    //this->results.founds.push_back(found);
                }
            NOT_FOUND_2:
                continue;
            }
        }
    }
    return hit;
}
bool TQueryManager::search_unquoted(TQuery& query, AVXFind& segment)
{
    auto frag_cnt = segment.fragments.size();

    if (frag_cnt < 1)
        return false;

    bool found = false;
    bool* hits = new bool[frag_cnt];
    for (uint8 b = 1; b <= 66; b++)
    {
        uint32 hit_cnt = 0;

        auto book = AVXBook::GetBook(b);
        auto writ = book.getWrit();
        auto until = writ + book.writ_cnt - 1;

        for (/**/; writ <= until; /**/)
        {
            uint32 cnt = 0;
            for (uint32 i = 0; i < frag_cnt; i++)
                hits[i] = false;
            uint16 span = query.settings.span > 0 ? query.settings.span : writ->wc;
            if (writ + span - 1 > until)
                span = (uint16)(until - writ);

            for (uint32 wi = 0; wi < span; wi++)
            {
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                found = false;

                for (auto frag : segment.fragments)
                {
                    bool hit = false; //  frag->compare(writ[wi], matched);
                    if (hit)
                    {
                        cnt++;
                        //hits[s] = true;
                    }
                    else break;
                }
                if (cnt >= frag_cnt)
                {
                    uint32 hit_cnt = 0;
                    for (uint32 s = 0; s < frag_cnt; s++)
                        if (hits[s])
                            hit_cnt++;

                    if (hit_cnt == frag_cnt)
                    {
                        found = true;
                        auto foundMatch = false; //  new TFound();
                        for (auto const& [coord, pair] : matched)
                        {
                            const char* frag = std::get<0>(pair);
                            const char* feat = std::get<0>(pair);
                            //auto match = new TMatch((uint32)coord, frag, feat);
                            //foundMatch->add(match);
                        }
                        //this->results.founds.push_back(foundMatch);
                    }
                }
            }
            if (query.settings.span == 0) // verse granularity
            {
                writ += span;
            }
            else
            {
                writ++;
            }
        }
    }
    delete[] hits;
    return found;
}