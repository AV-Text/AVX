#include "AVXBlueprint.h"
#include "AVXSearch.h"
#include "AVXFind.h"

#include <book.h>

#include <rapidjson/document.h>


AVXBlueprint::AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool auto_lemma_matching)
    : settings(span, lex, similarity, auto_lemma_matching)
{
    this->root.Parse(data);

    this->okay = false;

    for (rapidjson::Value::ConstMemberIterator itr = this->root.MemberBegin(); itr != this->root.MemberEnd(); ++itr)
    {
        const rapidjson::Value& expression = itr->value;
        this->searches.push_back(new AVXFind(expression));
        this->okay = true;
    }
}
AVXBlueprint::~AVXBlueprint()
{
    ;
}