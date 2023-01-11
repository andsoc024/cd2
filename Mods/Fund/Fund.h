// ============================================================================
// CD2
// Fundamentals Header
// by Andreas Socratous
// Jan 2023
// ============================================================================


#ifndef FUND_GUARD
#define FUND_GUARD


// ============================================================================ INFO
/*
    Functions for error handling, memory management, string and path 
    manipulation.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ============================================================================ FUNC DECL

// ---------------------------------------------------------------------------- Error Functions

void            Flow_FatalError(const char* errorMsg);
void            Flow_Assert(int condition, const char* errorMsg);

// ---------------------------------------------------------------------------- Memory Functions

void*           Memory_Allocate(void* ptr, int size);
void*           Memory_Copy(void* dst, const void* src, int size);
void            Memory_Write(void* dst, const void* src, int size);
void            Memory_Set(void* ptr, int size, unsigned char value);
void*           Memory_Free(void* ptr);
void            Memory_FreeAll(int nObjects, ...);

// ---------------------------------------------------------------------------- String Functions

int             String_Length(const char* str);
char*           String_Copy(char* dst, const char* src);
bool            String_IsEqual(const char* str1, const char* str2);
char*           String_Concat(char* dst, int nStrings, ...);
char*           String_PutInQuotes(char* str, const char* quote);
int             String_Find(const char* str, const char* subStr);
char*           String_Replace(char* str, const char* original, const char* change);

// ---------------------------------------------------------------------------- Path Functions

char*           Path_GetHomeDir(char* dst);
char*           Path_Append(char* path, const char* pathComp);

// ---------------------------------------------------------------------------- File Functions

char*           File_ReadStringFromFile(char* dst, FILE* file);
bool            File_Exists(const char* path);
bool            File_DirExists(const char* path);
bool            File_Delete(const char* path);

#endif // FUND_GUARD

