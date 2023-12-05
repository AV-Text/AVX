#pragma once
#include <avxgen.h>
#include <stdlib.h>
#include <directory.h>

#include <rapidjson/document.h>
#include <string>

class AVXComparator
{
private:
    AVXComparator(const rapidjson::Value& node, bool bad) : node(node), type("unknown"), feature(node["feature"].GetString()), negate(false), okay(false)
    {
        ;
    }
protected:
    AVXComparator(const rapidjson::Value& node) : node(node), type(node["type"].GetString()), feature(node["feature"].GetString()), negate(node["negate"].GetString()), okay(true)
    {
        ;
    }
public:
    static AVXComparator* Create(const rapidjson::Value& node);

    const rapidjson::Value& node;
    const char* feature;
    const char* rule;
    const bool negate;
    const bool okay;
    const bool type;

    virtual uint16 compare(const WrittenContent& writ)
    {
        return 0;
    }

    virtual ~AVXComparator()
    {
        ;
    }

    static const uint16 FullMatch = 1000;  // 100%
};

