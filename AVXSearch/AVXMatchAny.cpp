#include "AVXMatchAny.h"

#include <written.h>
#include <AVXComparator.h>

AVXMatchAny::AVXMatchAny(rapidjson::Value& options) : options(""), features(nullptr)
    // : options(xoption->option()->c_str()), features(nullptr)
{
    this->options = "foo-option"; // xoption->option()->c_str();
    //auto xfeatures = options["features"];
    //if (xfeatures != nullptr)
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
