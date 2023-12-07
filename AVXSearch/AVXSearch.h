#pragma once
#include "AVXBlueprint.h"
#include <unordered_set>
#include <vector>

#include <rapidjson/document.h>

#include <AVXFind.h>
#include <TQuery.h>

class AVXSearch
{
private:
 // const rapidjson::Value& segment;
 // AVXFind& results;
 // const AVXSettings& settings;

//  const char* spec;
//  bool quoted;
//  AVXFragment** requirements;

public:
    bool search_quoted(TQuery& query, AVXFind& segment);
    bool search_unquoted(TQuery& query, AVXFind& segment);

    inline const bool find(TQuery& query, AVXFind& segment)
    {
        bool found = segment.quoted ? search_quoted(query, segment) : search_unquoted(query, segment);
        return found;
    }

//  AVXSearch(rapidjson::Value& find, AVXFind& results, const AVXSettings& settings);
    AVXSearch();
    ~AVXSearch();
};