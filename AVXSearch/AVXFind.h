#pragma once
#include <avxgen.h>
#include <vector>
#include <string>
#include <blueprint_reply_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XBlueprint;

class AVXFound;

class AVXFind
{
public:
    std::vector<AVXFound*> founds;
    std::string find;
    bool negate;

    AVXFind()
    {
        this->negate = false;
        this->find = "";
    }
    AVXFind(bool negate, const char* search)
    {
        this->negate = negate;
        this->find = search;
    }
    ~AVXFind()
    {
        ;
    }
    void add(AVXFound* found);
    void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection);
};
    