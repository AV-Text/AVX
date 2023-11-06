#pragma once
#include <avxgen.h>
#include <directory.h>
#include <unordered_map>

const char AVXNames_File[] = "AV-Names.dxi";  // from AV-Inventory-Z31.bom
const uint32 AVXNames_RecordCnt =  2470; // from AV-Inventory-Z31.bom
const uint32 AVXNames_FileLen   = 60727; // from AV-Inventory-Z31.bom

class AVXNames
{
private:
    std::unordered_map<uint16, char*> names;
public:

    AVXNames(const NamesContent* const data, uint32 count);
    ~AVXNames();
};

extern AVXNames* name_lookup;