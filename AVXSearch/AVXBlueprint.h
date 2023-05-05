#pragma once
#include <avxgen.h>
#include <vector>

class AVXFind;

class AVXBlueprint
{
private:
    void* request;
public:
    AVXBlueprint(const uint8* const data);
    bool execute();

    std::vector<AVXFind*> searches;
    const uint8* const build();

    ~AVXBlueprint()
    {
        ;
    }
};