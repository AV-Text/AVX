#include "AVXFragment.h"
#include "AVXMatchAny.h"
#include <directory.h>

AVXFragment::AVXFragment(rapidjson::Value& fragments) : fragment(""), anchored(true), requirements(nullptr)
    //: fragment(xfragments->fragment()->c_str()), anchored(xfragments->anchored()), requirements(nullptr)
{
    /*
    auto xrequirements = xfragments->require();
    if (xfragments != nullptr)
    {
        int fragments_size = xrequirements->size();
        this->requirements = (AVXMatchAny**)calloc(fragments_size + 1, sizeof(AVXMatchAny*));
        for (int xreq = 0; xreq < fragments_size; xreq++)
        {
            auto xopt = (*xrequirements)[xreq];
            this->requirements[xreq] = new AVXMatchAny(xopt);
        }
    }
    */
}

AVXFragment::~AVXFragment()
{
    if (this->requirements != nullptr)
    {
        for (int i = 0; this->requirements[i] != nullptr; i++)
        {
            std::free((void*)this->requirements[i]);
        }
        std::free(this->requirements);
    }
}

bool AVXFragment::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    if (this->requirements != nullptr)
    {
        for (int i = 0; this->requirements[i] != nullptr; i++) // fragments are AND conditions (&)
            if (this->requirements[i]->compare(writ, matched) > 0)
                return true;
    }
    return false;
}
