#pragma once
#include <avxgen.h>
#include <directory.h>
#include <unordered_map>
const char AVXLemmaOOV_File[] = "AV-Lemma-OOV.dxi"; // from AV-Inventory-Z31.bom
const uint32 AXVLemmaOOV_RecordCnt  =  771;       // from AV-Inventory-Z31.bom
const uint32 AVXLemmaOOV_FileLen = 7754;       // from AV-Inventory-Z31.bom

// OOV: uint16                                   // from Digital-AV.pdf
const uint16 OOV_Marker = 0x8000;
const uint16 OOV_length = 0x0F00;
const uint16 OOV_index  = 0x000F;

class AVXLemmaOOV
{
private:
    std::unordered_map<uint16, char*> oov;
public:

    AVXLemmaOOV(const OOVContent* const data, uint32 count);
    ~AVXLemmaOOV();
};

extern AVXLemmaOOV* lemmata_oov;