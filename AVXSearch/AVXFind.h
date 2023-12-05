#pragma once
#include <avxgen.h>
#include <vector>
#include <string>

#include <rapidjson/document.h>

//class AVXFound;

class AVXFind
{
public:
//    std::vector<AVXFound*> founds;

    AVXFind(const rapidjson::Value& find): segment(find)
    {
        ;
    }
    ~AVXFind()
    {
        ;
    }
//    bool add(AVXFound* found);

private:
    const rapidjson::Value& segment;
};
    