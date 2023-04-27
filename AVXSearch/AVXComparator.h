#pragma once
#include <avxgen.h>
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <stdlib.h>
#include <written.h>

using namespace XBlueprint;

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
    virtual const char* compare(AVXWritten::AVXWrit& writ) = 0;

    virtual ~AVXComparator()
    {
        ;
    }
};

