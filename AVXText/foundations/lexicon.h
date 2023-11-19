#pragma once
#include <avxgen.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <directory.h>
#include <algorithm>

const char AVXLexicon_File[] = "AV-Lexicon.dxi"; // from AV-Inventory-Z31.bom
const uint32 AV_Lexicon_RecordCnt =  12567; // from AV-Inventory-Z31.bom
const uint32 AV_Lexicon_FileLen   = 246249; // from AV-Inventory-Z31.bom

// Entities: uint16
const uint16 Entity_Hitchcock     = 0x8000;
const uint16 Entity_men           =    0x1;
const uint16 Entity_women         =    0x2;
const uint16 Entity_tribes        =    0x4;
const uint16 Entity_cities        =    0x8;
const uint16 Entity_rivers        =   0x10;
const uint16 Entity_mountains     =   0x20;
const uint16 Entity_animals       =   0x40;
const uint16 Entity_gemstones     =   0x80;
const uint16 Entity_measurements  =  0x100;

inline const vector<uint32> GetPosVector(const LexiconContent& lex)
{
    vector<uint32> pos;
    for (int p = 0; p < lex.size; p++)
        pos.push_back((&(lex.pos))[p]);
    return pos;
}

inline const char* GetToken(const LexiconContent& lex)
{
    const uint32* const pos = &(lex.pos) + lex.size;
    const char* const token = (const char* const) pos;
    return token;
}

inline const char* GetDisplay(const LexiconContent& lex)
{
    const char* const token = GetToken(lex);
    const char* const display = token + Strnlen(token, 24) + 1;
    return display[0] != 0 ? display : token;
}

inline const char* GetModern(const LexiconContent& lex)
{
    const char* const token = GetToken(lex);
    const char* const display = token + Strnlen(token, 24) + 1;
    const char* const modern  = display + Strnlen(display, 24) + 1;

    return modern[0] != 0 ? modern : display[0] != 0 ? display : token;
}

inline bool CanBeModernized(const LexiconContent& lex)
{
    const char* const token = GetToken(lex);
    const char* const display = token + Strnlen(token, 24) + 1;
    const char* const modern = display + Strnlen(display, 24) + 1;

    return modern[0] != 0;
}

inline std::string NormalizeModern(const LexiconContent& lex)
{
    const char* const modern = GetModern(lex);
    std::string normalized(modern);
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    std::remove(normalized.begin(), normalized.end(), '-');
    normalized.erase();
    return normalized;
}

inline std::string NormalizeDisplay(const LexiconContent& lex)
{
    const char* const display = GetToken(lex);
    std::string normalized(display);

    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);

    return normalized;
}

class AVXLexKeyMap
{
private:
    LexiconContent* lexicon[AV_Lexicon_RecordCnt+1];
public:
    int add(const uint16 key, const LexiconContent& record)
    {
        if (key <= AV_Lexicon_RecordCnt)
        {
            this->lexicon[key] = &const_cast<LexiconContent&>(record);
            return 1;
        }
        return 0;
    }
    LexiconContent* get(const uint16 key)
    {
        const uint16 masked = key & 0x3FFF;
        return masked <= AV_Lexicon_RecordCnt && key >= 1 ? this->lexicon[masked] : nullptr;
    }

    AVXLexKeyMap()
    {
        ;
    }
    virtual ~AVXLexKeyMap()
    {
        ;
    }
};

class AVXLexTokenMap
{
private:
    std::unordered_map<std::string, uint16> kjv;
    std::unordered_map<std::string, vector<uint16>> mod;

    vector<uint16>* const GetExistingModernVector(const std::string &modern)
    {
        if (this->mod.find(const_cast<std::string&>(modern)) != this->mod.end())
        {
            return &(this->mod.at(const_cast<std::string&>(modern)));
        }
        return nullptr;
    }
public:
    static bool create_lexicon(const LexiconContent* const lex, uint32 count, bool createLexicalLookupMap);
    static bool delete_lexicon();

    int add(const uint16 key, const LexiconContent& lex);

    vector<uint16> LookupModern(const char* const token)
    {
        std::vector<uint16> records;
        auto modern = std::string(token);

        if (this->mod.find(modern) == this->mod.end())
        {
            std::transform(modern.begin(), modern.end(), modern.begin(), ::tolower);
            std::remove(modern.begin(), modern.end(), '-');

            if (this->mod.find(modern) == this->mod.end())
            {
                return records;
            }
        }
        modern.erase();
        return this->mod.at(modern);
    }
    const uint16 LookupOriginal(const char* const token)
    {
        std::vector<uint16> records;
        auto search = std::string(token);

        if (this->kjv.find(search) == this->kjv.end())
        {
            std::transform(search.begin(), search.end(), search.begin(), ::tolower);
            std::remove(search.begin(), search.end(), '-');

            if (this->kjv.find(search) == this->kjv.end())
            {
                return 0;
            }
        }
        search.erase();
        return this->kjv.at(search);
    }

    vector<uint16> LookupEither(const char* const token)
    {
        vector<uint16> results;

        auto av = this->LookupOriginal(token);
        auto avx = this->LookupModern(token);

        if (av != 0)
            results.push_back(av);
        for (auto result : avx)
            results.push_back(result);

        return results;
    }
    bool clear_lexicon();

    AVXLexTokenMap()
    {
        ;
    }
    virtual ~AVXLexTokenMap()
    {
        this->clear_lexicon();
    }
};

extern AVXLexTokenMap LexLookup;
extern AVXLexKeyMap   LexMap;

