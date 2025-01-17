#pragma once
#include <avxgen.h>
#include <vector>
#include <string>

class AVXFind;
class AVXFound;
class AVXMatch;

class AVXResult
{
public:
    std::vector<AVXFind*> finds;
    uint64 scope_ot;
    uint32 scope_nt;

    AVXResult()
    {
        this->scope_ot = 0;
        this->scope_nt = 0;
        this->current = nullptr;
    }
    ~AVXResult()
    {
        ;
    }
    bool add(AVXFind* find);
    bool add(AVXFound* found);
    bool add(AVXMatch* match);

    //bool build(flatbuffers::FlatBufferBuilder& builder, std::vector<flatbuffers::Offset<XFind>>& parentCollection);

private:
    AVXFind* current;
};
