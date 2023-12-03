#pragma once

#ifndef CPP_AVXGEN_H
#define CPP_AVXGEN_H

#include <stdint.h>
#include <widemath.h>
typedef uint8_t   byte;
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;

typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;

class uint128
{
private:
	uint128_t num;
public:
	uint128(uint128_t num128): num(num128)
	{
		;
	}
	uint128(uint64 high, uint64 low)
	{
		this->num.Q[0] = high;
		this->num.Q[1] = low;
	}
	uint128()
	{
		this->num.Q[0] = 0;
		this->num.Q[1] = 0;
	}
	bool operator<(const uint128& other) const // we need this so that we can have uint128 map<> keys
	{
		if (this->num.Q[0] == other.num.Q[0])
			return this->num.Q[1] < other.num.Q[1];

		return this->num.Q[0] < other.num.Q[0];
	}
	void operator=(const uint128& other)
	{
		this->num = { other.num.Q[0], other.num.Q[1] };
	}
	void operator=(const uint128_t& other)
	{
		this->num = other;
	}
	// Overloaded cast
	operator uint128_t() const { return num; }

};

#endif //CPP_AVXGEN_H
