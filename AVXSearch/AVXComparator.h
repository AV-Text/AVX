#pragma once
#include <avxgen.h>
#include <stdlib.h>
#include <directory.h>

#include <rapidjson/document.h>
#include <string>
#include <vector>

class TMatch;
class TTag;
class AVXComparator
{
private:
    AVXComparator(const rapidjson::Value& node, bool bad)
        : node(node)
        , type(node.HasMember("Type") ? node["Type"].GetString() : "")
        , feature(node.HasMember("Text") ? node["Text"].GetString() : "")
        , negate(node.HasMember("Negate") ? node["Negate"].GetBool() : false)
        , okay(false)
    {
        ;
    }
protected:
    AVXComparator(const rapidjson::Value& node)
        : node(node)
        , type(node.HasMember("Type") ? node["Type"].GetString() : "")
        , feature(node.HasMember("Text") ? node["Text"].GetString() : "")
        , negate(node.HasMember("Negate") ? node["Negate"].GetBool() : false)
        , okay(true)
    {
        ;
    }
public:
    static AVXComparator* Create(const rapidjson::GenericObject<true, rapidjson::Value>& node);

    const rapidjson::Value& node;
    const std::string type;
    const std::string feature;
    const bool negate;
    const bool okay;

    virtual uint16 compare(const WrittenContent& writ, TMatch& match, TTag& tag)
    {
        return 0;
    }

    virtual ~AVXComparator()
    {
        ;
    }

    static const uint16 FullMatch = 1000;  // 100%
};

