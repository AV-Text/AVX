#include "AVXFragment.h"

#include "AVXWordComparator.h"
#include "AVXLemmaComparator.h"
#include "AVXPOS16Comparator.h"
#include "AVXPOS32Comparator.h"
#include "AVXDeltaComparator.h"
#include "AVXPuncComparator.h"
#include "AVXStrongsComparator.h"

#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>

#include <written.h>

using namespace Blueprint::Request;

static AVXComparator* create_feature(const XFeature* feature)
{
    if (feature != nullptr)
    {
        auto rule = feature->rule()->c_str();

        if (std::strncmp(rule, "text", 4) == 0 || std::strncmp(rule, "wildcard", 8) == 0)
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
    }
    return nullptr;
}

AVXFragment::AVXFragment(const XFragment* xfragment) : fragment(xfragment->fragment()->c_str()), features(nullptr)
{
    auto xfeatures = xfragment->features();
    if (xfeatures != nullptr)
    {
        int features_size = xfeatures->size();
        this->features = (AVXComparator**)calloc(features_size + 1, sizeof(AVXComparator*));
        for (int f = 0; f < features_size; f++)
        {
            auto xfragment = (*xfeatures)[f];
            this->features[f] = create_feature(xfragment);
        }
    }
}

bool AVXFragment::compare(AVXWritten::AVXWrit& writ)
{
    return false;
}

AVXFragment::~AVXFragment()
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
