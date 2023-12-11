#include "AVXComparator.h"
#include "AVXWordComparator.h"
#include "AVXLemmaComparator.h"
#include "AVXPOS16Comparator.h"
#include "AVXPOS32Comparator.h"
#include "AVXDeltaComparator.h"
#include "AVXPuncComparator.h"
#include "AVXTransitionComparator.h"
#include "AVXStrongsComparator.h"

AVXComparator* AVXComparator::Create(const rapidjson::GenericObject<true, rapidjson::Value>& node)
{
    auto feature = node["Text"].GetString();

    if (feature != nullptr)
    {
        auto type = node["Type"].GetString();

        if (std::strncmp(type, "Word", 4) == 0 || std::strncmp(type, "Wildcard", 8) == 0)
        {
            return new AVXWordComparator(node);
        }
        if (std::strncmp(type, "PartOfSpeech", 12) == 0)
        {
            if (node.HasMember("PnPos12") && (node["PnPos12"].GetUint() > 0))
                return new AVXPOS16Comparator(node);
            if (node.HasMember("Pos32") && (node["Pos32"].GetUint() > 0))
                return new AVXPOS32Comparator(node);

            return new AVXComparator(node, false);
        }
        if (std::strncmp(type, "Lemma", 8) == 0)
        {
            return new AVXLemmaComparator(node);
        }
        if (std::strncmp(type, "Delta", 8) == 0)
        {
            return new AVXDeltaComparator(node);
        }
        if (std::strncmp(type, "Punctuation", 11) || std::strncmp(type, "Decoration", 10) == 0)
        {
            return new AVXPuncComparator(node);
        }
        if (std::strncmp(type, "Strongs", 8) == 0)
        {
            return new AVXStrongsComparator(node);
        }
        if (std::strncmp(type, "Transition", 8) == 0)
        {
            return new AVXTransitionComparator(node);
        }
    }
    return new AVXComparator(node, false); // comparisons are ALWAYS false in the base-class; this is a fail-safely error condition
}