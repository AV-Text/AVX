#ifndef WINDOWS_XVMem_HEADER
#define WINDOWS_XVMem_HEADER

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 
#include <malloc.h> 
#include <stdio.h> 

#define    ImportLib    __declspec( dllimport ) 
#define    ExportLib    __declspec( dllexport )

// min() and max macros break the c4core library ... disable them
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif


inline char* Strncpy(char* destination, const char* name, uint32_t len) {
#pragma warning(suppress : 4996)
    return strncpy(destination, name, len);
}
inline uint32_t Strnlen(const char* str, uint32_t maxlen) {
#pragma warning(suppress : 4996)
    return (uint32_t) strnlen(str, maxlen);
}
inline uint32_t Strnlen(char* str, uint32_t maxlen) {
#pragma warning(suppress : 4996)
    return (uint32_t)strnlen(str, maxlen);
}

#endif    //WINDOWS_XVMem_HEADER