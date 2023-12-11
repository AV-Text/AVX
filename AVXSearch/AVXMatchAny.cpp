#include "AVXMatchAny.h"

#include <written.h>
#include <AVXComparator.h>
#include <vector>

AVXMatchAny::AVXMatchAny(rapidjson::GenericObject<true, rapidjson::Value>& opts) : matchany(opts)
{
    this->okay = false;
    this->options = "";

    if (this->matchany["AnyFeature"].IsArray())
    {
        auto array = this->matchany["AnyFeature"].GetArray();

        for (auto feature = array.Begin(); feature != array.End(); ++feature)
        {
            rapidjson::GenericObject<true, rapidjson::Value> option = feature->GetObj();
            AVXComparator * comparator = AVXComparator::Create(option);
            this->features.push_back(comparator);
            this->okay = true;

            if (this->options.length() > 0)
                this->options += '|';
            this->options += comparator->feature;
        }
    }

    if (this->error.empty() && !this->okay)
    {
        error = "Unable to extract any fragments from the search expression";
    }
}

// OBSOLETE FUNCTION (no longer used)
/*
bool AVXMatchAny::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    for (AVXComparator* feature : this->features)
    {
        auto hit = feature->compare(writ);
        if (hit > 0)
        {
            auto coord = WritAsCoordinate(writ);
            auto result = std::make_tuple(this->options, (const uint16)hit);
            matched.emplace(coord, result);
            return true;
        }
    }
    return false;
}*/

AVXMatchAny::~AVXMatchAny()
{
    ;
}
