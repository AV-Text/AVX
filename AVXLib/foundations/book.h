#pragma once
#include <avxgen.h>
#include <book.h>
#include <chapter.h>

const char AVXBookIndex_File[] = "AV-Book.ix";   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_RecordLen = 44;   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_RecordCnt = 67;   // from AV-Inventory-Z31.bom
const uint32 AVXBookIndex_FileLen = 2948;   // from AV-Inventory-Z31.bom

#include <directory.h>

extern bool reset_omega(DirectoryContent* directory); // this function resave the omega file (it currently fixes a bug in omega-3.2, and revs the version to omega-3.5

class AVXBook {
private:
    static const char empty[1];
    static AVXBook* Book[67];
    static const char* const indexed_substring(const char* const str, uint8 idx)
    {
        if (idx == 0)
        {
            return str;
        }
        char* result = const_cast<char*>(str);
        int remainder = 9;
        int len = 0;
        for (uint8 i = 0; i < idx; i++)
        {
            int len = Strnlen(result, remainder);
            result += (len + 1);
            remainder -= (len + 1);

            if (remainder < 2)
                return AVXBook::empty;
        }
        for (int i = 0; i < remainder; i++)
        {
            if (result[i] == 0) // found null-termination
            {
                return result;
            }
        }
        return AVXBook::empty;
    }
    static const uint16 const count_verses(const ChapterContent const* chap, uint8 chapter_cnt)
    {
        if (chapter_cnt == 0 || chap == nullptr)
        {
            return 0;
        }
        uint16 v = 0;
        for (uint8 c = 0; c < chapter_cnt; c++)
        {
            v += chap[c].verse_count;
        }
        return v;
    }

public:
    const uint8     num;
    const uint8     chapter_cnt;
    const uint16    chapter_idx;
    const uint16    verse_cnt;
    const uint16    writ_cnt;
    const uint32    writ_idx;
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
        verse_cnt(count_verses(chap, book.chapter_count)),
        writ_cnt(book.writ_count),
        writ_idx(book.writ_index),
        name  {(&book.text)[0], (&book.text)[1], (&book.text)[2], (&book.text)[3], (&book.text)[4], (&book.text)[5], (&book.text)[6], (&book.text)[7], (&book.text)[8], (&book.text)[9], (&book.text)[10], (&book.text)[11], (&book.text)[12], (&book.text)[13], (&book.text)[14], (&book.text)[15], 0 },
        abbr2 {(&book.text)[16], (&book.text)[17], 0 },
        abbr3 {(&book.text)[18], (&book.text)[19], (&book.text)[20], 0 },
        abbr4 {(&book.text)[21], (&book.text)[22], (&book.text)[23], (&book.text)[24], 0 },
        abbrAlt1((&book.text)+25),
        abbrAlt2(indexed_substring((&book.text) + 25, 1)),
        abbrAlt3(indexed_substring((&book.text) + 25, 2)),
        writ(writ),
        chapters(chap)
    {
        if (this->num <= 66)
        {
            AVXBook::Book[this->num] = this;
        }
        if (this->verse_cnt != book.verse_count)
        {
            printf("%02d:\t%d != %d\n", (int)book.num, (int)this->verse_cnt, (int)book.verse_count);
        }
    }
    inline static const AVXBook& GetBook(uint8 num)
    {
        if (num <= 66)
            return *(AVXBook::Book[num]);

        return *(AVXBook::Book[0]);
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