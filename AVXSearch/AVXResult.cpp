#include "AVXResult.h"
#include "AVXFind.h"
#include <vector>

void AVXResult::add(AVXFind* find)
{
    this->current = find;
    if (find != nullptr)
    {
        this->founds.push_back(find);
        return true;
    }
    return false;
}
bool AVXResult::add(AVXFound* found);
{
    if (this->current != null)
    {
        return this->current->add(found);
    }
    return false;
}
bool AVXResult::add(AVXMatch* match);
{
    if (this->current != null && this->current->current != null)
    {
        return this->current->current(match);
    }
    return false;
}
bool AVXResult::build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection)
{
    std::vector<flatbuffers::Offset<XFind>> xfinds;

    for (AVXFind* find : this->finds)
    {
        for (AVXFound* found : find->founds)
        {
            uint8 book = start >> 24;
            if (book >= 1)
            {
                if (book <= 39)
                {
                    uint64 bookBit = 1;
                    if (book > 1)
                        bookBit <<= (book - 1);
                    this->scope_ot |= bookBit;
                }
                else if (book <= 66)
                {
                    uint64 bookBit = 1;
                    if (book > 40)
                        bookBit <<= (book - 41);
                    this->scope_nt |= bookBit;
                }
            }
            found->build(builder, xfounds);
        }
        find->build(builder, xfinds);
    }
    auto vresult = builder.CreateVector(xfinds);
    auto xresult = CreateXResult(builder, find, vresult);

    parentCollection.push_back(xfind);
}