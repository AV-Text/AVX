#pragma once
#include <avxgen.h>
#include <vector>

#include <ryml.hpp>
#include <AVXSettings.h>

class AVXFind;

class AVXBlueprint
{
private:
    ryml::Tree tree;
    bool okay;

public:
    AVXBlueprint(char data[], uint16 span=0, byte lex=1, byte similarity=100, bool auto_lemma_matching=false);

    const AVXSettings settings;
    std::vector<AVXFind*> searches;
    inline bool isOkay() { return okay; }

    ryml::ConstNodeRef request;

    ~AVXBlueprint();
};