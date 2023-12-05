#pragma once
#include <avxgen.h>
#include <vector>

#include <AVXSettings.h>

#include <rapidjson/document.h>

class AVXFind;

class AVXBlueprint
{
private:
    rapidjson::Document root; 
    bool okay;

public:
    AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool auto_lemma_matching);

    const AVXSettings settings;
    std::vector<AVXFind*> searches;
    inline bool isOkay() { return okay; }

//  rapidjson::Value& request;

    ~AVXBlueprint();
};