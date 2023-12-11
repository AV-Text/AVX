#pragma once

#include <avxgen.h>

const byte LEX_AV = 1;
const byte LEX_AVX = 2;
const byte LEX_BOTH = 3;

class AVXSettings
{
public:
    const byte lexicon;
    const byte similarity;
    const bool enable_lemma_matching;
    const uint16 span;
    AVXSettings(uint16 span, byte lex, byte similarity, bool enable_lemma_matching) :
        lexicon(lex),
        similarity(similarity),
        enable_lemma_matching(enable_lemma_matching),
        span(span)
    {
        ;
    }
};
