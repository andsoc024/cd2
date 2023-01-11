// ============================================================================
// CD2
// String
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ INFO
/*
    Functions for string manipulation.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdarg.h>

#include "Fund.h"


// ============================================================================ FUNC DEF

// **************************************************************************** String_Length

// Return the number of characters in the string, excluding the terminator
int String_Length(const char* str){
    int length = 0;
    for (; *str != '\0'; str++){
        length++;
    }

    return length;
}


// **************************************************************************** String_Copy

// Copy the string from src to dst
char* String_Copy(char* dst, const char* src){
    return Memory_Copy(dst, src, String_Length(src) + 1);
}


// **************************************************************************** String_IsEqual

// Return true if the two strings are the same
bool String_IsEqual(const char* str1, const char* str2){
    if (str1 == NULL || str2 == NULL){
        return false;
    }

    for (; *str1 != '\0' && *str2 != '\0'; str1++, str2++){
        if (*str1 != *str2){
            return false;
        }
    }

    return *str1 == *str2;
}


// **************************************************************************** String_Concat

// Concatenate the strings and save the result at dst
char* String_Concat(char* dst, int nStrings, ...){
    // If the number of strings is invalid, return an empty string
    if (nStrings <= 0){
        return String_Copy(dst, "");
    }

    // Pointer to the string list in the arguments
    va_list argPtr;

    // Determine the length of the concatenated string
    int length = 0;
    va_start(argPtr, nStrings);
    for (int i = 0; i < nStrings; i++){
        char* temp = va_arg(argPtr, char*);
        if (temp == NULL) {continue;}
        length += String_Length(temp);
    }
    va_end(argPtr);

    // Allocate memory at a new string, in case dst is also in the string list 
    // in the arguments
    char* res = Memory_Allocate(NULL, length + 1);
    char* ptr = res;

    // Concatenate the strings
    va_start(argPtr, nStrings);
    for (int i = 0; i < nStrings; i++){
        char* temp = va_arg(argPtr, char*);
        if (temp == NULL) {continue;}
        for (; *temp != '\0'; temp++, ptr++){
            *ptr = *temp;
        }
    }
    va_end(argPtr);

    // Free the memory at dst
    dst = Memory_Free(dst);

    // Return the concatenated string
    return res;
}


// **************************************************************************** String_PutInQuotes

// Add quote at the beginning and the end of the string
char* String_PutInQuotes(char* str, const char* quote){
    return String_Concat(str, 3, quote, str, quote);
}


// **************************************************************************** String_Find

// Return the position of the first encounter of subStr in str, starting at 0. 
// If not found, return -1
int String_Find(const char* str, const char* subStr){
    int strLength = String_Length(str);
    int subStrLength = String_Length(subStr);

    for (int i = 0; i <= strLength - subStrLength; i++){
        bool found = true;
        for (int j = 0; j < subStrLength; j++){
            if (*(str + i + j) != *(subStr + j)){
                found = false;
                break;
            }
        }
        if (found){
            return i;
        }
    }

    return -1;
}


// **************************************************************************** String_Replace

// Replace all the occurences of the original in str, with change
char* String_Replace(char* str, const char* original, const char* change){
    int index = 0;

    int subStrLength = String_Length(original);

    while ((index = String_Find(str, original)) >= 0){
        char* leftPart = Memory_Allocate(NULL, index + 1);
        Memory_Write(leftPart, str, index);
        str = String_Concat(str, 3, leftPart, change, str + index + subStrLength);
        leftPart = Memory_Free(leftPart);
    }

    return str;
}


