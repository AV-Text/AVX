#pragma once
#include <avxgen.h>
#include <directory.h>
#include <unordered_map>
const char AVXLemmata_File[] = "AV-Lemma.dxi"; // from AV-Inventory-Z31.bom
const uint32 AVXLemmata_RecordCnt  =  15171;   // from AV-Inventory-Z31.bom
const uint32 AVXLemmata_FileLen    = 182344;   // from AV-Inventory-Z31.bom

class AVXLemmata
{
private:
    std::unordered_map<uint64, LemmataContent*> lemmata;
public:

    AVXLemmata(const LemmataContent* const data, uint32 count);
    ~AVXLemmata();
};

extern AVXLemmata* lemmata_lookup;