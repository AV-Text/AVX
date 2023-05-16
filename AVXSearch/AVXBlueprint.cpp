#include "AVXBlueprint.h"
#include "AVXSearch.h"
#include "AVXFind.h"
#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprintBlue;
using namespace XSearchResults;

#include <book.h>

AVXBlueprint::AVXBlueprint(const uint8* const data)
{
    const XBlueprint* req = GetXBlueprint(data);
    this->settings = new AVXSettings(req->settings());

    this->request = (void*)req;
}
AVXBlueprint::~AVXBlueprint()
{
    if (this->settings != nullptr)
        delete this->settings;
}
bool AVXBlueprint::execute()
{
    const XBlueprint* req = reinterpret_cast<const XBlueprint*>(this->request);

    if (req->status() == XStatusEnum_ERROR)
    {
        ; // report error
    }
    else if (req->singleton() != nullptr)
    {
        if (req->status() == XStatusEnum_ACTION_REQUIRED)
        {
            ; // take approriate action (like display history or help)
        }
    }
    else if (req->search() != nullptr)
    {
        auto xsearch = req->search();
        if (xsearch != nullptr)
        {
            vector<AVXScope*> scopes;
            auto xscopes = req->scope();
            if (xscopes != nullptr)
            {
                int xscopes_size = xscopes->size();
                for (int x = 0; x < xscopes_size; x++)
                {
                    auto xscope = (*xscopes)[x];
                    auto scope = new AVXScope(xscope);
                    scopes.push_back(scope);
                }
            }

            int search_size = xsearch->size();
            for (int r = 0; r < search_size; r++)
            {
                auto rxsearch = (*xsearch)[r];
                auto expression = new AVXFind(rxsearch->negate(), rxsearch->search()->c_str());
                this->searches.push_back(expression);
                auto search = new AVXSearch(rxsearch, *expression, *this->settings);

                search->find(scopes);
            }
            if (req->status() == XStatusEnum_FEEDBACK_EXPECTED)
            {
                ; // return data to pipe
            }
            else
            {
                ; // this is unexpected
            }
        }
        else
        {
            ; // this is unexpected
        }
    }
    else if (req->status() != XStatusEnum_COMPLETED)
    {
        ; // unknown/undefined status
    }
    return false;
}

const uint8* const AVXBlueprint::build(uint32 &size)
{
    size = 0;
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

    size = (uint32) builder.GetSize();
    auto buffer = new uint8[size];
    builder.PushFlatBuffer(buffer, size);
    return buffer;
}