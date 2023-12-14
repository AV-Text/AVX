#pragma once

#include <rapidjson/document.h>
#include <string>
#include <avxgen.h>

class AVX
{
public:
	static std::string GetString(const char *key, const rapidjson::GenericObject<true, rapidjson::Value>& node, char * default_val = "")
	{
		return node.HasMember(key) ? node[key].GetString() : default_val;
	}
	static std::string GetString(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, char* default_val = "")
	{
		return node.HasMember(key) ? node[key].GetString() : default_val;
	}

	static uint64 GetUInt64(const char* key, const rapidjson::GenericObject<true, rapidjson::Value>& node, uint64 default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetUint64() : default_val;
	}
	static uint64 GetUInt64(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, uint64 default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetUint64() : default_val;
	}

	static uint32 GetUInt32(const char* key, const rapidjson::GenericObject<true, rapidjson::Value>& node, uint32 default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetUint() : default_val;
	}
	static uint32 GetUInt32(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, uint32 default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetUint() : default_val;
	}

	static uint16 GetUInt16(const char* key, const rapidjson::GenericObject<true, rapidjson::Value>& node, uint16 default_val = 0)
	{
		uint32 val = node.HasMember(key) ? uint32(node[key].GetUint()) : uint32(default_val);

		return (0xFFFF0000 & val) == 0 ? uint16(val) : default_val;
	}
	static uint16 GetUInt16(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, uint16 default_val = 0)
	{
		uint32 val = node.HasMember(key) ? uint32(node[key].GetUint()) : uint32(default_val);

		return (0xFFFF0000 & val) == 0 ? uint16(val) : default_val;
	}

	static byte GetByte(const char* key, const rapidjson::GenericObject<true, rapidjson::Value>& node, byte default_val = 0)
	{
		uint32 val = node.HasMember(key) ? uint32(node[key].GetUint()) : uint32(default_val);

		return (0xFFFFFF00 & val) == 0 ? byte(val) : default_val;
	}
	static byte GetByte(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, byte default_val = 0)
	{
		uint32 val = node.HasMember(key) ? uint32(node[key].GetUint()) : uint32(default_val);

		return (0xFFFFFF00 & val) == 0 ? byte(val) : default_val;
	}

	static bool GetBool(const char* key, const rapidjson::GenericObject<true, rapidjson::Value>& node, bool default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetBool() : default_val;
	}
	static bool GetBool(const char* key, rapidjson::GenericObject<false, rapidjson::Value>& node, bool default_val = 0)
	{
		return node.HasMember(key) ? node[key].GetBool() : default_val;
	}
};