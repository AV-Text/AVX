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
private:
    static byte similarity_from_input(const XSettings* settings)
    {
        std:string value = settings->similarity()->c_str();
        auto len = value.length();
        if (len > 0)
        {
            if (value.c_str()[len-1] == '!')
                value = value.substr(0, --len); 
        }
        int ival = 0;
        if (len > 0)
        {
            if (value == "exact")
                ival = 100;
            else if (value == "none")
                ival = 0;
            else
            {
                for (int i = 0; i < len; i++)
                {
                    ival *= 10;

                    char c = value[i];
                    if (c >= '0' && c <= '9')
                        ival += (int)(c - '0');
                    else
                        return (byte) 0;

                    if (ival > XThreshold::XThreshold_EXACT)
                        return (byte) 0;
                }
                return ival >= XThreshold::XThreshold_FUZZY_MIN && ival <= XThreshold::XThreshold_EXACT ? (byte)ival : (byte)0;
            }
        }
        return (byte)0;
    }
    static bool lemma_matching_from_input(const XSettings* settings)
    {
        bool lemma_matching = (settings->lexicon() != XLexEnum::XLexEnum_AV);

        if (lemma_matching)
        {
            std:string value = settings->similarity()->c_str();
            auto len = value.length();
            if (len > 0)
            {
                if (value.c_str()[len - 1] == '!')
                    return false;
            }
            int ival = 0;
            if (len > 0)
            {
                if (value == "exact")
                    return true;
                else if (value == "none")
                    return false;
                else
                {
                    for (int i = 0; i < len; i++)
                    {
                        ival *= 10;

                        char c = value[i];
                        if (c >= '0' && c <= '9')
                            ival += (int)(c - '0');
                        else
                            return false;

                        if (ival > XThreshold::XThreshold_EXACT)
                            return false;
                    }
                    return (ival >= XThreshold::XThreshold_FUZZY_MIN) && (ival <= XThreshold::XThreshold_EXACT) ? true : false;
                }
            }
        }
        return false;
    }
public:
    const XLexEnum lexicon;
    const XOutEnum display;
    const byte similarity;
    const bool automatic_lemma_matching;
    const uint16 span;
    const XFmtEnum format;
    AVXSettings(const XSettings* settings) :
        lexicon(settings->lexicon()),
        display(settings->display()),
        similarity(AVXSettings::similarity_from_input(settings)),
        automatic_lemma_matching(AVXSettings::lemma_matching_from_input(settings)),
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