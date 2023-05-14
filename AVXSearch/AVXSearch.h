#pragma once
#include "AVXBlueprint.h"
#include <unordered_set>
#include <vector>

#include <blueprint_blue_generated.h>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprintBlue;

class AVXSettings
{
public:
    const XLexEnum lexicon;
    const bool exact;
    const uint16 span;
    const XFmtEnum format;
    AVXSettings(const XSettings* settings) :
        lexicon(settings->lexicon()),
        exact(settings->exact()),
        span(settings->span()),
        format(settings->format())
    {
        ;
    }
};
class AVXScope
{
public:
    const uint8 book;
    const uint8 chapter;   // required
    const uint8 verse;     // optional
    const uint8 vcount;    // optional: verse-count: defaults to all remaining verses in chapter

    AVXScope(const XScope* xscope) :
        book(xscope->book()),
        chapter(xscope->chapter()),
        verse(xscope->verse()),
        vcount(xscope->vcount())
    {
        ;
    }
};

class AVXSegment;
class AVXSearch
{
private:
    const XSearch* xsearch;
    AVXFind& results;
    const AVXSettings& settings;
    std::vector<const AVXScope*> scopes;

    const char* spec;
    bool negate;
    bool quoted;
    AVXSegment** segments;
    XSegment* xsegments;

public:
    bool search_quoted(vector<AVXScope*>& scopes);
    bool search_unquoted(vector<AVXScope*>& scopes);

    inline const AVXFind& find(vector<AVXScope*>& scopes)
    {
        bool found = this->quoted ? search_quoted(scopes) : search_unquoted(scopes);
        return this->results;
    }

    AVXSearch(const XSearch* xsearch, AVXFind& results, const AVXSettings& settings);
    ~AVXSearch();
    void add_scope(const AVXScope* scope);
};