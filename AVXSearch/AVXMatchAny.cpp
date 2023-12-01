#include "AVXMatchAny.h"

#include "AVXWordComparator.h"
#include "AVXLemmaComparator.h"
#include "AVXPOS16Comparator.h"
#include "AVXPOS32Comparator.h"
#include "AVXDeltaComparator.h"
#include "AVXPuncComparator.h"
#include "AVXTransitionComparator.h"
#include "AVXStrongsComparator.h"

#include <written.h>

static AVXComparator* create_feature(ryml::ConstNodeRef feature)
{
    if (feature != nullptr)
    {
        auto rule = "foo-rule"; // feature->rule()->c_str();

        if (std::strncmp(rule, "word", 4) == 0 || std::strncmp(rule, "wildcard", 8) == 0)
        {
            return new AVXWordComparator(feature);
        }
        if (std::strncmp(rule, "pnpos", 4) == 0)
        {
            return new AVXPOS16Comparator(feature);
        }
        if (std::strncmp(rule, "pos32", 8) == 0)
        {
            return new AVXPOS32Comparator(feature);
        }
        if (std::strncmp(rule, "lemma", 8) == 0)
        {
            return new AVXLemmaComparator(feature);
        }
        if (std::strncmp(rule, "delta", 8) == 0)
        {
            return new AVXDeltaComparator(feature);
        }
        if (std::strncmp(rule, "punctuation", 11) || std::strncmp(rule, "decoration", 10) == 0)
        {
            return new AVXPuncComparator(feature);
        }
        if (std::strncmp(rule, "strongs", 8) == 0)
        {
            return new AVXStrongsComparator(feature);
        }
        if (std::strncmp(rule, "transition", 8) == 0)
        {
            return new AVXTransitionComparator(feature);
        }
    }
    return nullptr;
}

AVXMatchAny::AVXMatchAny(ryml::ConstNodeRef options) : options(""), features(nullptr)
    // : options(xoption->option()->c_str()), features(nullptr)
{
    this->options = "foo-option"; // xoption->option()->c_str();
    auto xfeatures = options["features"];
    if (xfeatures != nullptr)
    {
        /*
        int features_size = xfeatures->size();
        this->features = (AVXComparator**)calloc(features_size + 1, sizeof(AVXComparator*));
        for (int f = 0; f < features_size; f++)
        {
            auto xfeature = (*xfeatures)[f];
            this->features[f] = create_feature(xfeature);
        }
        */
    }
}

bool AVXMatchAny::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    if (this->features != nullptr) // features are OR conditions (|)
    {
        for (int i = 0; this->features[i] != nullptr; i++)
        {
            auto hit = this->features[i]->compare(writ);
            if (hit > 0)
            {
                auto coord = WritAsCoordinate(writ);
                auto result = std::make_tuple(this->options, (const uint16)hit);
                matched.emplace(coord, result);
                return true;
            }
        }
        return false;
    }
    return false;
}

AVXMatchAny::~AVXMatchAny()
{
    if (this->features != nullptr)
    {
        for (int i = 0; this->features[i] != nullptr; i++)
        {
            std::free((void*)this->features[i]);
        }
        std::free(this->features);
    }
}
