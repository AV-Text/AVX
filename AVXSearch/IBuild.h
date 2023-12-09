#pragma once

#include <Serialization.h>

class IBuild// Interface
{
public:
	virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder) = 0;
	virtual ~IBuild() { ; }
};
