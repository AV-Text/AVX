#include "AVXBlueprint.h"
#include "AVXSearch.h"
#include "AVXFind.h"

#include <book.h>

#include <ryml.hpp>
#include <ryml_std.hpp>

AVXBlueprint::AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool auto_lemma_matching)
    : settings(span, lex, similarity, auto_lemma_matching)
{
    int len = strlen(data);
    char yaml[32*1024];    // TO DO (TODO): Why does this need to be fixed size on the stack?
    yaml[len] = '\0';
    for (int i = 0; i < len; i++)
        yaml[i] = data[i];

    this->tree = ryml::parse_in_place(yaml);
    this->okay = false;

    this->request = tree.crootref();
    auto expression = this->request["searches"];
    for (auto search : expression)
    {
        this->searches.push_back(new AVXFind(search));
        this->okay = true;
    }
}
AVXBlueprint::~AVXBlueprint()
{
    ;
}