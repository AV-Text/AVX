#include "AVXFound.h"
#include "AVXMatch.h"

void AVXFound::add(AVXMatch* match)
{
    if (match != nullptr)
    {
        this->matches.push_back(match);

        if (match->coordinates < this->start)
        {
            this->start = match->coordinates;
        }
        if (match->coordinates > this->until)
        {
            this->until = match->coordinates;
        }
    }
}
void AVXFound::build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFound>>& parentCollection)
{
    std::vector<flatbuffers::Offset<XMatch>> xmatches;

    for (AVXMatch* match : this->matches)
    {
        match->build(builder, xmatches);
    }
    auto vmatches = builder.CreateVector(xmatches);
    auto found = CreateXFound(builder, start, until, vmatches);

    parentCollection.push_back(found);
}
