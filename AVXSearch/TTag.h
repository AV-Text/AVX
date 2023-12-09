///////////////////////////////////////////////////////////
//  TMatch.h
//  Implementation of the Class TMatch
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#if !defined(EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_)
#define EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_

#include <Serialization.h>
#include <string>
#include <vector>
#include <IBuild.h>

class TTag : public IBuild
{
public:
    uint16 feature;
    uint32 coordinates;

    TTag(uint32 coordinates, uint16 feature)
    {
        this->feature = feature;
        this->coordinates = coordinates;
    }
    virtual ~TTag()
    {
        ;
    }

    virtual void build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
    {
        builder.StartObject();
        builder.Key("feature");
        builder.Uint(this->feature);
        builder.Key("coordinates");
        builder.Uint(this->coordinates);
        builder.EndObject();
    }
    
    inline byte get_book()
    {
        return byte(coordinates & 0xFF00 >> 24);
    }
    inline byte get_chapter()
    {
        return byte(0xFF & (coordinates >> 16));
    }
    inline byte get_verse()
    {
        return byte(0xFF & (coordinates >> 8));
    }
    inline byte word()
    {
        return byte(0xFF & coordinates);
    }
    inline static uint32 CreateCoordinate(byte b, byte c, byte v, byte w)
    {
        return (uint32(b) << 24) | (uint32(c) << 16) | (uint32(v) << 8) | uint32(w);
    }

    static std::string byte_to_string(byte input)
    {
        char num[4] = { '0', '0', '0', '\0' };
        int position = 3;
        byte val = input;
        do
        {
            num[--position] = val % 10;
            val /= 10;

        }   while (val != 0);

        return num;
    }
};
#endif // !defined(EA_0242817E_0000_4662_9FD8_C11A766FDD3F__INCLUDED_)
