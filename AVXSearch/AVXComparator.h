#pragma once
#include <avxgen.h>
#include <stdlib.h>
#include <directory.h>

#include <ryml.hpp>

class AVXComparator
{
protected:
    AVXComparator(ryml::ConstNodeRef feature) : feature("foo"), negate(false), rule("foo-rule")
        // : feature(feature->feature()->c_str()), negate(feature->negate()), rule(feature->rule()->c_str())
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

