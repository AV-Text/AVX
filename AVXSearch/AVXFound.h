#pragma once
#include <avxgen.h>
#include <vector>
#include <blueprint_reply_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprint;

class AVXMatch;

class AVXFound
{
public:
    uint32 start;
    uint32 until;
    std::vector<AVXMatch*> matches;

    AVXFound()  // start/until determined in add() method
    {
        this->start = 0;
        this->until = 0xFFFFFFFF;
    }
    AVXFound(uint32 start, uint32 until)
    {
        this->start = start;
        this->until = until;
    }
    ~AVXFound()
    {
        ;
    }
    void add(AVXMatch* match);
    void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFound>>& parentCollection);
};

