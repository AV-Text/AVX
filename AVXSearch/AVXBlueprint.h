#pragma once
#include <avxgen.h>
#include <vector>

#include <ryml.hpp>

class AVXFind;
class AVXSettings;

class AVXBlueprint
{
private:
    ryml::Tree tree;
    AVXSettings* settings;
public:
    AVXBlueprint(char data[], uint16 span=0, byte lex=1, byte similarity=100, bool auto_lemma_matching=false);
    bool execute();

    std::vector<AVXFind*> searches;
    bool build();

    ryml::ConstNodeRef request;

    ~AVXBlueprint();
};