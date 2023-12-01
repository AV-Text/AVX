#include "AVXBlueprint.h"
#include "AVXSearch.h"
#include "AVXFind.h"

#include <book.h>

AVXBlueprint::AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool auto_lemma_matching)
{
    c4::substr str;
    if (ryml::from_chars(str, data))
    {
        this->tree = ryml::parse_in_place(str);
        this->request = tree.crootref();
        this->settings = new AVXSettings(span, lex, similarity, auto_lemma_matching);
    }

}
AVXBlueprint::~AVXBlueprint()
{
    if (this->settings != nullptr)
        delete this->settings;
}
bool AVXBlueprint::execute()
{
    int search_size = searches.size();
    for (auto search : searches)
    {
        /*
        auto expression = new AVXFind(search);
        this->searches.push_back(expression);
        auto search = new AVXSearch(rxsearch, *expression, *this->settings);

        search->find();
        */
    }
}

bool AVXBlueprint::build()
{
    for (AVXFind* search : this->searches)
    {
        ; // search->build(builder, collection);
    }
/*
    auto vcollection = builder.CreateVector(collection);
    xresults.add_results(vcollection);

    std::vector<flatbuffers::Offset<uint32>> empty_scope;

    auto results = xresults.Finish();
    size = (uint32) builder.GetSize();
    auto buffer = new uint8[size];
    builder.PushFlatBuffer(buffer, size);
    return buffer;
*/
    return false;
}