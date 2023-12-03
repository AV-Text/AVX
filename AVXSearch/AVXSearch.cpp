#include "AVXSearch.h"
#include "AVXFragment.h"
#include "AVXBlueprint.h"
#include "AVXFind.h"
#include "AVXFound.h"
#include "AVXMatch.h"
#include <map>
#include <directory.h>
#include <book.h>

static std::unordered_set<uintptr_t> MemoryTable;

bool AVXSearch::search_quoted()
{
    uint32 seg_cnt = 0;
    if (this->requirements == nullptr)
        return false;
    for (/**/; this->requirements[seg_cnt]; seg_cnt++)
        ;
    if (seg_cnt == 0)
        return false;

    bool hit = false;
    for (uint8 b = 1; b <= 66; b++)
    {
        auto book = AVXBook::GetBook(b);
        auto writ = book.getWrit();

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
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                bool found = this->requirements[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    auto spanwrit = writ + 1;

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
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                bool found = this->requirements[0]->compare(*writ, matched);
                if (found)
                {
                    uint32 wi = w;
                    uint32 wi_len = wi + len;

                    auto spanwrit = writ + 1;

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
    if (this->requirements == nullptr)
        return false;
    for (/**/; this->requirements[seg_cnt]; seg_cnt++)
        ;
    if (seg_cnt == 0)
        return false;

    bool found = false;
    bool *hits = new bool[seg_cnt];
    for (uint8 b = 1; b <= 66; b++)
    {
        uint32 hit_cnt = 0;

        auto book = AVXBook::GetBook(b);
        auto writ = book.getWrit();
        auto until = writ + book.writ_cnt - 1;

        for (/**/; writ <= until; /**/)
        {
            uint32 cnt = 0;
            for (uint32 i = 0; i < seg_cnt; i++)
                hits[i] = false;
            uint16 span = this->settings.span > 0 ? this->settings.span : writ->wc;
            if (writ + span - 1 > until)
                span = (uint16)(until - writ);

            for (uint32 wi = 0; wi < span; wi++)
            {
                std::map<uint32, std::tuple<const char*, const uint16>> matched;
                found = false;
                for (uint32 s = 0; (!found) && (s < seg_cnt); s++)
                {
                    bool hit  = this->requirements[s]->compare(writ[wi], matched);
                    if (hit)
                    {
                        cnt++;
                        hits[s] = true;
                    }
                    else break;
                }
                if (cnt >= seg_cnt)
                {
                    uint32 hit_cnt = 0;
                    for (uint32 s = 0; s < seg_cnt; s++)
                        if (hits[s])
                            hit_cnt++;

                    if (hit_cnt == seg_cnt)
                    {
                        found = true;
                        auto foundMatch = new AVXFound();
                        for (auto const& [coord, pair] : matched)
                        {
                            const char* frag = std::get<0>(pair);
                            const char* feat = std::get<0>(pair);
                            auto match = new AVXMatch((uint32)coord, frag, feat);
                            foundMatch->add(match);
                        }
                        this->results.founds.push_back(foundMatch);
                    }
                }
            }
            if (this->settings.span == 0) // verse granularity
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

/*
    const XSearch* xsearch;
    AVXFind& results;
    const AVXSettings& settings;
    std::vector<const AVXScope*> scopes;

    const char* spec;
    bool quoted;
    AVXFragment** requirements;
    */
AVXSearch::AVXSearch(ryml::ConstNodeRef find, AVXFind& results, const AVXSettings& settings):
    segment(find),
    results(results),
    settings(settings), 
    spec("foo-spec"), //spec(xsearch->expression()->c_str()),
    quoted(false), //quoted(xsearch->quoted()),
    requirements(nullptr)
{
    /*
    auto fragments = this->segment["fragments"];

    if (fragments != nullptr)
    {
        int segments_size = fragments->size();
        this->requirements = (AVXFragment**) (std::calloc(segments_size + 1, sizeof(AVXFragment*)));
        for (int s = 0; s < segments_size; s++)
        {
            auto fragment = (*fragments)[s];
            if (fragment != nullptr)
            {
                this->requirements[s] = new AVXFragment(fragment);
            }
        }
    }
    */
}
AVXSearch::~AVXSearch()
{
    if (this->requirements != nullptr)
    {
        for (int i = 0; this->requirements[i] != nullptr; i++)
        {
            std::free((void*)this->requirements[i]);
        }
        std::free(this->requirements);
    }
}





