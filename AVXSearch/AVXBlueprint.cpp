#include "AVXBlueprint.h"
#include "AVXFind.h"

#include <book.h>

#include <rapidjson/document.h>


AVXBlueprint::AVXBlueprint(char data[], uint16 span, byte lex, byte similarity, bool auto_lemma_matching)
    : settings(span, lex, similarity, auto_lemma_matching)
{
    this->okay = false;
    
    rapidjson::Document root;
    root.Parse(data);
    if (root.IsArray())
    {
        auto array = root.GetArray();

        for (auto segment = array.Begin(); segment != array.End(); ++segment)
        {
            rapidjson::GenericObject<false, rapidjson::Value> expression = segment->GetObj();
            this->searches.push_back(new AVXFind(expression));
            this->okay = true;
        }
    }
    else
    {
        error = "Unable to parse search blueprint";
    }
    if (this->error.empty() && !this->okay)
    {
        error = "Unable to extract any search blueprint";
    }
}
AVXBlueprint::~AVXBlueprint()
{
    ;
}