#pragma once
#include "cyrus-container.h"
/*
#ifdef CYRUS_EXPORTS
#define CYRUSLIBRARY_API __declspec(dllexport)
#else
#define CYRUSLIBRARY_API __declspec(dllimport)
#endif
#define ADDCALL __cdecl
#ifdef __cplusplus
extern "C" {
#endif    
CYRUSLIBRARY_API */
void * ReadCyrusFile(const char* str);
/*#ifdef __cplusplus
}
#endif  */ 