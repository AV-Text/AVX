#pragma once
#include <avxgen.h>
#include <string>
#include <blueprint_reply_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprint;

class AVXMatch
{
public:
    std::string fragment;
    std::string feature;
    uint32 coordinates;

    AVXMatch(const char* fragment, const char* feature, uint32 coordinates)
    {
        this->fragment = fragment;
        this->feature = feature;
        this->coordinates = coordinates;
    }
    ~AVXMatch()
    {
        ;
    }
    void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XMatch>>& parentCollection);
};

