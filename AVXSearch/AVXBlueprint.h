#pragma once
#include <avxgen.h>
#include <vector>

class AVXFind;
class AVXSettings;

class AVXBlueprint
{
private:
    void* request;
    AVXSettings* settings;
public:
    AVXBlueprint(const uint8* const data);
    bool execute();

    std::vector<AVXFind*> searches;
    const uint8* const build(uint32& size);

    inline void* getRequest()
    {
        return this->request;
    }

    ~AVXBlueprint();
};