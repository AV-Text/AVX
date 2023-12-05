#pragma once
#include "AVXBlueprint.h"
#include <unordered_set>
#include <vector>

#include <rapidjson/document.h>

class AVXFragment;
class AVXSearch
{
private:
    const rapidjson::Value& segment;
    AVXFind& results;
    const AVXSettings& settings;

    const char* spec;
    bool quoted;
    AVXFragment** requirements;

public:
    bool search_quoted();
    bool search_unquoted();

    inline const AVXFind& find()
    {
        bool found = this->quoted ? search_quoted() : search_unquoted();
        return this->results;
    }

    AVXSearch(rapidjson::Value& find, AVXFind& results, const AVXSettings& settings);
    ~AVXSearch();
};