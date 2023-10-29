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
        this->current = nullptr;
    }
    AVXFind(const char* search)
    {
        this->find = search;
        this->current = nullptr;
    }
    ~AVXFind()
    {
        ;
    }
    bool add(AVXFound* found);
    void build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection);

private:
    AVXFound* current;
public:
    inline AVXFound* getCurrent()
    {
        return this->current;
    }
};
    