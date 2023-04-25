#pragma once
#include <avxgen.h>
#include <vector>

class AVXFind;

class AVXResults
{
private:
    void* request;
public:
    AVXResults(const uint8* const data);
    bool execute();

    std::vector<AVXFind*> searches;
    const uint8* const build();

    ~AVXResults()
    {
        ;
    }
};