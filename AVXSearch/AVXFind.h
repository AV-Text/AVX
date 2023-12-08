#pragma once
#include <avxgen.h>
#include <vector>
#include <string>

#include <rapidjson/document.h>
#include <AVXFragment.h>
//class AVXFound;

class AVXFind
{
public:
//    std::vector<AVXFound*> founds;

    friend class AVXBlueprint;

    AVXFind(const rapidjson::GenericObject<false, rapidjson::Value>& expression): segment(expression), quoted(expression["isQuoted"].GetBool())
    {
        this->okay = false;
        if (this->segment.IsObject())
        {
            if (this->segment["fragments"].IsArray())
            {
                auto array = this->segment["fragments"].GetArray();

                for (auto fragment = array.Begin(); fragment != array.End(); ++fragment)
                {
                    rapidjson::GenericObject<true, rapidjson::Value> frag = fragment->GetObj();
                    this->fragments.push_back(new AVXFragment(frag));
                    this->okay = true;
                }
            }
            if (this->okay && this->segment.IsString())
            {
                this->expression = this->segment.GetString();
            }
        }
        else
        {
            error = "Unable to parse search expression";
        }
        if (this->error.empty() && !this->okay)
        {
            error = "Unable to extract any fragments from the search expression";
        }
    }
    ~AVXFind()
    {
        ;
    }
    const bool quoted;
    std::vector<const AVXFragment*> fragments;
    std::string expression;

//    bool add(AVXFound* found);

private:
    const rapidjson::Value& segment;
    std::string error;
    bool okay;
};
    