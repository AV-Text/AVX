#pragma once
#include <avxgen.h>
#include <vector>
#include <string>

#include <AVXSettings.h>

class AVXFind;

class AVXBlueprint
{
private:
//    rapidjson::Document root; 
    std::string error;
    bool okay;

public:
    AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool enable_lemma_matching);

    const AVXSettings settings;
    std::vector<AVXFind*> searches;
    inline bool isOkay() { return okay; }

//  rapidjson::Value& request;

    ~AVXBlueprint();
};