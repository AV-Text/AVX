#pragma once
#include <avxgen.h>
#include <string>

class AVXMatch
{
public:
    std::string fragment;
    std::string feature;
    uint32 coordinates;

    AVXMatch(uint32 coordinates, const char* fragment, const char* feature)
    {
        this->fragment = fragment;
        this->feature = feature;
        this->coordinates = coordinates;
    }
    ~AVXMatch()
    {
        ;
    }
    //void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XMatch>>& parentCollection);
};

