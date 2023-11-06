#pragma once
#include <avxgen.h>
const char AVXChapterIndex_File[] = "AV-Chapter.ix";    // from AV-Inventory-Z31.bom
const uint32 AVXChapterIndex_RecordLen =    8;     // from AV-Inventory-Z31.bom
const uint32 AVXChapterIndex_RecordCnt = 1189;     // from AV-Inventory-Z31.bom
const uint32 AVXChapterIndex_FileLen   = 9512;     // from AV-Inventory-Z31.bom

struct AVXChapter {
public:
    const uint16 writ_idx;
    const uint16 writ_cnt;
    const uint8  book_num;
    const uint8  verse_cnt;
};