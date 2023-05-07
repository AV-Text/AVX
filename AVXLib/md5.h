#include <avxgen.h>

//extern std::string md5(const std::string& filename);
extern bool md5(const uint8 const* content, uint32 size, uint64& hi, uint64& lo);