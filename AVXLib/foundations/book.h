#pragma once
#include <avxgen.h>
#include <book.h>
#include <chapter.h>

const char AVXBookIndex_File[] = "AV-Book.ix";   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_RecordLen = 44;   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_RecordCnt = 67;   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_FileLen = 2948;   // from AV-Inventory-Z31.bom

#include <directory.h>

class AVXBook {
private:
    char  _alternates[10];
    uint8 _baseAlt2;
    uint8 _baseAlt3;
    static AVXBook* Book[67];
public:
    const uint8     num;
    const uint8     chapter_cnt;
    const uint16    chapter_idx;
    const uint16    verse_cnt;
    const uint16    writ_cnt;
    const char      name[17];
    const char      abbr2[3];  // strlen == 2 || strlen == 0
    const char      abbr3[4];  // strlen == 3
    const char      abbr4[5];  // <-- Most common // use this for display // strlen <= 4
    const char* const abbrAlt1;  // Alternate Abbreviations (maximum of three)
    const char* const abbrAlt2;  // Alternate Abbreviations (maximum of three)
    const char* const abbrAlt3;  // Alternate Abbreviations (maximum of three)
    const WrittenContent* writ;
    const ChapterContent* chapters;

    AVXBook(const BookContent& book, const ChapterContent const* chap, const WrittenContent const* writ, const DirectoryContent const* directory) :
        num(book.num),
        chapter_cnt(book.chapter_count),
        chapter_idx(book.chapter_index),
        verse_cnt(book.verse_count),
        writ_cnt(book.writ_count),
        name  {book.name[0], book.name[1], book.name[2], book.name[3], book.name[4], book.name[5], book.name[6], book.name[7], book.name[8], book.name[9], book.name[10], book.name[11], book.name[12], book.name[13], book.name[14], book.name[15], 0 },
        abbr2 {book.abbr2[0], book.abbr2[1], 0 },
        abbr3 {book.abbr3[0], book.abbr3[1], book.abbr3[2], 0 },
        abbr4 {book.abbr4[0], book.abbr4[1], book.abbr4[2], book.abbr4[3], 0 },
        _alternates {book.abbr_alt[0], book.abbr_alt[1], book.abbr_alt[2], book.abbr_alt[3], book.abbr_alt[4], book.abbr_alt[5], book.abbr_alt[6], book.abbr_alt[7], book.abbr_alt[8], 0 },
        _baseAlt2(book.abbr_alt[0] != 0 ? Strnlen(book.abbr_alt, 9) + 1 : 0),
        _baseAlt3(_baseAlt2 < 9 && book.abbr_alt[_baseAlt2] != 0 ? Strnlen(book.abbr_alt + _baseAlt2, 9 - _baseAlt2) + 1 : 0),
        abbrAlt1(this->_alternates),
        abbrAlt2(_baseAlt2 > 0 ? this->_alternates + _baseAlt2 : this->_alternates + 9),
        abbrAlt3(_baseAlt3 > 0 ? this->_alternates + _baseAlt3 : this->_alternates + 9),
        writ(writ),
        chapters(chap)
    {
        if (this->num <= 66)
        {
            AVXBook::Book[this->num] = this;
        }
    }
    inline static const AVXBook& GetBook(uint8 num)
    {
        if (num <= 66)
            return *(AVXBook::Book[num]);
    }
        
    const WrittenContent* const getWrit(uint8 chapter = 1)
    {
        if (chapter > this->chapter_cnt || chapter < 1)
            return nullptr;

        auto ichapter = this->chapters + chapter - 1;
        return this->writ + ichapter->writ_index;
    }
    const WrittenContent* const getWrit(uint8 chapter, uint8 verse)
    {
        if (chapter > this->chapter_cnt || chapter < 1)
            return nullptr;

        auto ichapter = this->chapters + chapter - 1;

        if (verse > ichapter->verse_count || verse < 1)
            return nullptr;

        auto writ_idx = ichapter->writ_index;
        auto iwrit = const_cast<WrittenContent*>(this->writ);

        for (uint8 v = 1; v < verse; v++)
        {
            iwrit += iwrit->wc;
        }
        return iwrit;
    }
};