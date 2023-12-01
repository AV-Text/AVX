#pragma once
#include "AVXBlueprint.h"
#include <unordered_set>
#include <vector>

#include <ryml.hpp>

const byte LEX_AV = 1;
const byte LEX_AVX = 2;
const byte LEX_BOTH = 3;

class AVXSettings
{
public:
    const byte lexicon;
    const byte similarity;
    const bool automatic_lemma_matching;
    const uint16 span;
    AVXSettings(uint16 span, byte lex, byte similarity, bool auto_lemma_matching) :
        lexicon(lex),
        similarity(similarity),
        automatic_lemma_matching(auto_lemma_matching),
        span(span)
    {
        ;
    }
};

class AVXFragment;
class AVXSearch
{
private:
    ryml::ConstNodeRef segment;
    AVXFind& results;
    const AVXSettings& settings;

    const char* spec;
    bool quoted;
    AVXFragment** requirements;

public:
    bool search_quoted();
    bool search_unquoted();

    inline const AVXFind& find()
    {
        bool found = this->quoted ? search_quoted() : search_unquoted();
        return this->results;
    }

    AVXSearch(ryml::ConstNodeRef find, AVXFind& results, const AVXSettings& settings);
    ~AVXSearch();
};