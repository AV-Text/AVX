#include "AVXFragment.h"
#include "AVXMatchAny.h"
#include <directory.h>

AVXFragment::AVXFragment(rapidjson::GenericObject<true, rapidjson::Value>& frag) : fragment(frag), anchored(frag["anchored"].GetBool())
{
    this->okay = false;

    if (this->fragment["requirements"].IsArray())
    {
        auto array = this->fragment["requirements"].GetArray();

        for (auto fragment = array.Begin(); fragment != array.End(); ++fragment)
        {
            rapidjson::GenericObject<true, rapidjson::Value> reqs = fragment->GetObj();
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

bool AVXFragment::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    for (auto req : this->requirements) // fragments are AND conditions (&)
        if (req->compare(writ, matched) > 0)
            return true;

    return false;
}
