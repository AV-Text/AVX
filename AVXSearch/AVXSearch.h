#pragma once
#include "AVXResults.h"
#include <unordered_set>
#include <book_index.h>
#include <unordered_set>
#include <vector>

#include <blueprint_request_generated.h>
#include <blueprint_reply_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace Blueprint::Request;
using namespace Blueprint::Reply;

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
    AVXResults& results;
    AVXSettings& settings;
    std::vector<const AVXScope*> scopes;

    const char* spec;
    bool negate;
    bool quoted;
    AVXSegment** segments;
    XSegment* xsegments;

public:
    bool search_quoted();
    bool search_unquoted();

    inline bool execute()
    {
        return this->quoted ? search_quoted() : search_unquoted();
    }

    AVXSearch(const XSearch* xsearch, AVXResults& results, const AVXSettings& xsettings);
    ~AVXSearch();
    void add_scope(const AVXScope* scope);
};