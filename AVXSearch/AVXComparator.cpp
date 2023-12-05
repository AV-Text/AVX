#include "AVXComparator.h"
#include "AVXWordComparator.h"
#include "AVXLemmaComparator.h"
#include "AVXPOS16Comparator.h"
#include "AVXPOS32Comparator.h"
#include "AVXDeltaComparator.h"
#include "AVXPuncComparator.h"
#include "AVXTransitionComparator.h"
#include "AVXStrongsComparator.h"

AVXComparator* AVXComparator::Create(const rapidjson::Value& node)
{
    auto feature = node["feature"].GetString();

    if (feature != nullptr)
    {
        auto rule = node["rule"].GetString();

        if (std::strncmp(rule, "word", 4) == 0 || std::strncmp(rule, "wildcard", 8) == 0)
        {
            return new AVXWordComparator(node);
        }
        if (std::strncmp(rule, "pnpos", 4) == 0)
        {
            return new AVXPOS16Comparator(node);
        }
        if (std::strncmp(rule, "pos32", 8) == 0)
        {
            return new AVXPOS32Comparator(node);
        }
        if (std::strncmp(rule, "lemma", 8) == 0)
        {
            return new AVXLemmaComparator(node);
        }
        if (std::strncmp(rule, "delta", 8) == 0)
        {
            return new AVXDeltaComparator(node);
        }
        if (std::strncmp(rule, "punctuation", 11) || std::strncmp(rule, "decoration", 10) == 0)
        {
            return new AVXPuncComparator(node);
        }
        if (std::strncmp(rule, "strongs", 8) == 0)
        {
            return new AVXStrongsComparator(node);
        }
        if (std::strncmp(rule, "transition", 8) == 0)
        {
            return new AVXTransitionComparator(node);
        }
        return new AVXComparator(node, false); // comparisons are ALWAYS false; this is a fail-safely error condition
    }
    return nullptr;
}