#pragma once
#include <avxgen.h>
#include <vector>
#include <string>
#include <avx_search_generated.h>
#include <flatbuffers/flatbuffers.h>

using namespace XSearchResults;

class AVXFound;

class AVXFind
{
public:
    std::vector<AVXFound*> founds;
    std::string find;

    AVXFind()
    {
        this->find = "";
    }
    AVXFind(const char* search)
    {
        this->find = search;
    }
    ~AVXFind()
    {
        ;
    }
    void add(AVXFound* found);
    void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection);
};
    