#pragma once
#include <avxgen.h>
#include <blueprint_request_generated.h>
#include <flatbuffers/flatbuffers.h>
#include <stdlib.h>

using namespace Blueprint::Request;

class AVXWritten;
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
    virtual bool compare(AVXWritten& writ) = 0;

    virtual ~AVXComparator()
    {
        ;
    }
};

