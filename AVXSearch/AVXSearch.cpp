#include "AVXSearch.h"
#include "AVXSegment.h"
#include "AVXBlueprint.h"
#include "AVXFind.h"
#include "AVXFound.h"
#include "AVXMatch.h"
#include <map>
#include <directory.h>
#include <book.h>
#include <flatbuffers/flatbuffers.h>
#include <blueprint_blue_generated.h>

static std::unordered_set<uintptr_t> MemoryTable;

bool AVXSearch::search_quoted()
{
    uint32 seg_cnt = 0;
    if (this->segments = nullptr)
        return false;
    for (/**/; this->segments[seg_cnt]; seg_cnt++)
        ;
    if (seg_cnt == 0)
        return false;

    bool hit = false;
    for (uint8 b = 1; b <= 66; b++)
    {
        auto book = AVXBook::GetBook(b);
        auto chap = book.chapters;
        auto writ = book.getWrit();
        uint8 c = 1;
        uint8 v = 1;

        uint32 w;

        if (this->settings.span > 0)
        {
            uint32 len = 0;
            for (w = 0; w < book.writ_cnt; w++, writ++)
            {
                if (len == 0)
                {
                    len = w + this->settings.span;
                    if (len > book.writ_cnt)
                        len = book.writ_cnt;
                }
                std::map<uint32, std::tuple<const char*, const char*>> matched;
                bool found = this->segments[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    uint32 wi_len = wi + len;

                    auto spanwrit = writ + 1;

                    for (uint32 seg_idx = 1; this->segments[seg_idx]; seg_idx++)
                    {
                        for (auto& segment = *(this->segments[seg_idx]); wi < len; wi++, spanwrit++)
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
                    auto found = new AVXFound();
                    for (auto const& [coord, pair] : matched)
                    {
                        const char* frag = std::get<0>(pair);
                        const char* feat = std::get<0>(pair);
                        auto match = new AVXMatch((uint32) coord, frag, feat);
                        found->add(match);
                    }
                    this->results.founds.push_back(found);
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
                std::map<uint32, std::tuple<const char*, const char*>> matched;
                bool found = this->segments[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    uint32 wi_len = wi + len;

                    auto spanwrit = writ + 1;

                    for (uint32 seg_idx = 1; this->segments[seg_idx]; seg_idx++)
                    { 
                        for (auto& segment = *(this->segments[seg_idx]); wi < wi_len; wi++, spanwrit++)
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
                    auto found = new AVXFound();
                    for (auto const& [coord, pair] : matched)
                    {
                        const char* frag = std::get<0>(pair);
                        const char* feat = std::get<0>(pair);
                        auto match = new AVXMatch((uint32)coord, frag, feat);
                        found->add(match);
                    }
                    this->results.founds.push_back(found);
                }
            NOT_FOUND_2:
            continue;
            }
        }
    }
    return hit;
}
bool AVXSearch::search_unquoted()
{
    uint32 seg_cnt = 0;
    if (this->segments == nullptr)
        return false;
    for (/**/; this->segments[seg_cnt]; seg_cnt++)
        ;
    if (seg_cnt == 0)
        return false;

    bool found = false;
    bool *hits = new bool[seg_cnt];
    for (uint8 b = 1; b <= 66; b++)
    {
        uint32 hit_cnt = 0;

        auto book = AVXBook::GetBook(b);
        auto chap = book.chapters;
        auto writ = book.getWrit();
        uint8 c = 1;
        uint8 v = 1;

        for (uint32 w = 0; w < book.writ_cnt; w++)
        {
            auto spanwrit = writ;
            uint32 cnt = 0;
            for (uint32 i = 0; i < seg_cnt; i++)
                hits[i] = false;
            uint32 until = w + this->settings.span > 0 ? this->settings.span - 1 : writ->wc - 1;
            if (until > book.writ_cnt - 1)
                until = book.writ_cnt - 1;
            for (uint32 wi = w; wi <= until; wi++, spanwrit++)
            {
                std::map<uint32, std::tuple<const char*, const char*>> matched;
                bool found = this->segments[0]->compare(*spanwrit, matched);
                for (uint32 s = 1; (!found) && (s < seg_cnt); s++)
                {
                    found = this->segments[s]->compare(*spanwrit, matched);
                    if (found)
                    {
                        cnt++;
                        hits[s] = true;
                    }
                    else break;
                }
                if (cnt == 0 && wi == w)
                    break;

                if (cnt >= seg_cnt)
                {
                    uint32 hit_cnt = 0;
                    for (uint32 i = 0; i < seg_cnt; i++)
                        hit_cnt++;

                    if (hit_cnt == seg_cnt)
                    {
                        found = true;
                        auto found = new AVXFound();
                        for (auto const& [coord, pair] : matched)
                        {
                            const char* frag = std::get<0>(pair);
                            const char* feat = std::get<0>(pair);
                            auto match = new AVXMatch((uint32)coord, frag, feat);
                            found->add(match);
                        }
                        this->results.founds.push_back(found);
                        break;
                    }
                }
            }
            if (this->settings.span == 0) // verse granularity
                writ += writ->wc;
            else
                writ ++;
        }
    }
    delete[] hits;
    return found;
}
void AVXSearch::add_scope(const AVXScope* scope)
{
    this->scopes.push_back(scope);
}

AVXSearch::AVXSearch(const XSearch* xsearch, AVXFind& results, const AVXSettings& xsettings):
    spec(xsearch->search()->c_str()),
    negate(this->xsearch->negate()),
    quoted(this->xsearch->quoted()),
    xsearch(xsearch),
    settings(settings),
    results(results),
    segments(nullptr)
{
    auto xsegments = this->xsearch->segments();

    if (xsegments != nullptr)
    {
        int segments_size = xsegments->size();
        this->segments = (AVXSegment**) (std::calloc(segments_size + 1, sizeof(AVXSegment*)));
        for (int s = 0; s < segments_size; s++)
        {
            auto xsegment = (*xsegments)[s];
            if (xsegment != nullptr)
            {
                this->segments[s] = new AVXSegment(xsegment);
            }
        }
    }
}
AVXSearch::~AVXSearch()
{
    if (this->segments != nullptr)
    {
        for (int i = 0; this->segments[i] != nullptr; i++)
        {
            std::free((void*)this->segments[i]);
        }
        std::free(this->segments);
    }
}

static void SayHello_defunct(const char* const command)
{/*
    flatbuffers::FlatBufferBuilder builder;
    auto cmd_offset = builder.CreateString(command);
    auto request_offset = CreateQuelleRequest(builder, cmd_offset);
    builder.Finish(request_offset);*/
}

// Do we need header defines for these?
extern "C" const uint8* const avx_create_search(const char* const request)
{/*
    AVXBlueprint search(request);
    search.execute();
    auto results = search.build();
	if (results != nullptr)
	{
		MemoryTable.insert(reinterpret_cast<uintptr_t>(results));
	}
	return results;*/
    return nullptr;
}
extern "C" bool avx_delete_search(const uint8* const* results)
{/*
	auto entry = reinterpret_cast<uintptr_t>(results);
	auto memory = reinterpret_cast<char*>(entry);

	auto it = MemoryTable.find(entry);
	if (it != MemoryTable.end()) {
		MemoryTable.erase(it);
		free(memory);
		return true;
	}*/
	return false;
}





