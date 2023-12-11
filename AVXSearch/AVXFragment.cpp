#include "AVXFragment.h"
#include "AVXMatchAny.h"
#include <directory.h>

AVXFragment::AVXFragment(rapidjson::GenericObject<true, rapidjson::Value>& frag) : fragment(frag), anchored(frag["Anchored"].GetBool())
{
    this->okay = false;

    if (this->fragment["MatchAll"].IsArray())
    {
        auto array = this->fragment["MatchAll"].GetArray();

        for (auto options = array.Begin(); options != array.End(); ++options)
        {
            rapidjson::GenericObject<true, rapidjson::Value> reqs = options->GetObj();
            this->requirements.push_back(new AVXMatchAny(reqs));
            this->okay = true;
        }
    }

    if (this->error.empty() && !this->okay)
    {
        error = "Unable to extract any fragments from the search expression";
    }
}

AVXFragment::~AVXFragment()
{
    ;
}

// OBSOLETE FUNCTION (no longer used)
/*
bool AVXFragment::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    for (auto req : this->requirements) // fragments are AND conditions (&)
        if (req->compare(writ, matched) > 0)
            return true;

    return false;
}*/
