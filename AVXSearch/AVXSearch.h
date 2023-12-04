#pragma once
#include "AVXBlueprint.h"
#include <unordered_set>
#include <vector>

#include <ryml.hpp>

class AVXFragment;
class AVXSearch
{
private:
    ryml::ConstNodeRef segment;
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

    AVXSearch(ryml::ConstNodeRef find, AVXFind& results, const AVXSettings& settings);
    ~AVXSearch();
};