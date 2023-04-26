#include "AVXSegment.h"
#include "AVXFragment.h"
#include <written.h>

using namespace XBlueprint;

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

bool AVXSegment::compare(AVXWritten::AVXWrit& writ)
{
    return false;
}
