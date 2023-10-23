#pragma once
#include <avxgen.h>
#include <blueprint_blue_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <stdlib.h>
#include <directory.h>

using namespace XBlueprintBlue;

class AVXComparator
{
protected:
    AVXComparator(const XFeature* feature) : feature(feature->feature()->c_str()), negate(feature->negate()), rule(feature->rule()->c_str())
    {
        ;
    }
public:
    const char* feature;
    const char* rule;
    const bool negate;

    virtual uint16 compare(const WrittenContent& writ) = 0;

    virtual ~AVXComparator()
    {
        ;
    }

    static const uint16 FullMatch = 1000;  // 100%
};

