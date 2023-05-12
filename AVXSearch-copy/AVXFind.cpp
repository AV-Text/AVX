#include "AVXFind.h"
#include "AVXFound.h"
#include <vector>

void AVXFind::add(AVXFound* found)
{
    if (found != nullptr)
    {
        this->founds.push_back(found);
    }
}
void AVXFind::build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection)
{
    std::vector<flatbuffers::Offset<XFound>> xfounds;

    for (AVXFound* found : this->founds)
    {
        found->build(builder, xfounds);
    }
    auto vfounds = builder.CreateVector(xfounds);
    auto find = builder.CreateString(this->find.c_str());
    auto xfind = CreateXFind(builder, find, negate, vfounds);

    parentCollection.push_back(xfind);
}
