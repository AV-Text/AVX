#include "AVXBlueprint.h"
#include "AVXSearch.h"
#include "AVXFind.h"
#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprintBlue;
using namespace XSearchResults;

#include <book_index.h>

AVXBlueprint::AVXBlueprint(const uint8* const data)
{
    const XBlueprint* req = GetXBlueprint(data);
    this->request = (void*)req;
}
bool AVXBlueprint::execute()
{
    const XBlueprint* req = reinterpret_cast<const XBlueprint*>(this->request);
    AVXSettings settings(req->settings());

    ; // TODO: implement search()
    auto books = AVXBookIndex::index;
    auto chapters = AVXChapterIndex::index;

    for (uint8 b = 1; b <= 66; b++)
    {
        auto book = books + b;
        auto chap = chapters + book->chapter_idx;
        auto writ = AVXWritten::getWrit(b);
        uint8 c = 1;
        uint8 v = 1;

        for (uint32 w = 0; w < book->writ_cnt; w++, writ++)
        {
            auto xsearch = req->search();
            if (xsearch != nullptr)
            {
                int search_size = xsearch->size();
                for (int r = 0; r < search_size; r++)
                {
                    auto rxsearch = (*xsearch)[r];
                    auto find = new AVXFind(rxsearch->negate(), rxsearch->search()->c_str());
                    this->searches.push_back(find);
                    AVXSearch search(rxsearch, *find, settings);

                    // This is redundant for multiple searches, but neither time-complexity nor memory bloat is not a real concern here
                    // This makes the search cleaner 9and thiere is often only one anyway most of the time)
                    auto xscopes = req->scope();
                    if (xscopes != nullptr)
                    {
                        int xscopes_size = xscopes->size();
                        for (int x = 0; x < xscopes_size; x++)
                        {
                            auto xscope = (*xscopes)[x];
                            auto scope = new AVXScope(xscope);
                            search.add_scope(scope);

                        }
                    }
                    search.execute();
                }
            }
        }
    }
    return false;
}

const uint8* const AVXBlueprint::build()
{
    std::vector<flatbuffers::Offset<XFind>> collection;
    flatbuffers::FlatBufferBuilder builder;
    XResultsBuilder xresults(builder);

    for (AVXFind* search : this->searches)
    {
        search->build(builder, collection);
    }
    auto vcollection = builder.CreateVector(collection);
    xresults.add_results(vcollection);

    std::vector<flatbuffers::Offset<uint32>> empty_scope;

    auto results = xresults.Finish();

    auto size = builder.GetSize();
    auto buffer = new uint8[size];
    builder.PushFlatBuffer(buffer, size);
    return buffer;
}