#include "AVXSegment.h"
#include "AVXFragment.h"
#include <directory.h>

using namespace XBlueprintBlue;

AVXSegment::AVXSegment(const XSegment* xsegments): segment(xsegments->segment()->c_str()), anchored(xsegments->anchored()), fragments(nullptr)
{
    auto xfragments = xsegments->fragments();
    if (xfragments != nullptr)
    {
        int fragments_size = xfragments->size();
        this->fragments = (AVXFragment**)calloc(fragments_size + 1, sizeof(AVXFragment*));
        for (int frag = 0; frag < fragments_size; frag++)
        {
            auto xfragment = (*xfragments)[frag];
            this->fragments[frag] = new AVXFragment(xfragment);
        }
    }
}

AVXSegment::~AVXSegment()
{
    if (this->fragments != nullptr)
    {
        for (int i = 0; this->fragments[i] != nullptr; i++)
        {
            std::free((void*)this->fragments[i]);
        }
        std::free(this->fragments);
    }
}

bool AVXSegment::compare(const WrittenContent& writ, std::map<uint32, std::tuple<const char*, const uint16>>& matched)
{
    if (this->fragments != nullptr)
    {
        for (int i = 0; this->fragments[i] != nullptr; i++) // fragments are AND conditions (&)
            if (this->fragments[i]->compare(writ, matched) > 0)
                return true;
    }
    return false;
}
