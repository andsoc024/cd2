// ============================================================================
// CD2
// System
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ INFO
/*
    Functions for error handling and memory management.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdarg.h>

#include "Fund.h"


// ============================================================================ FUNC DEF

// ---------------------------------------------------------------------------- Error Functions

// **************************************************************************** Flow_FatalError

// Print the error message and exit with exit code 1
void Flow_FatalError(const char* errorMsg){
    if (errorMsg != NULL){
        printf("ERROR! %s\n", errorMsg);
    }
    exit(1);
}


// **************************************************************************** Flow_Assert

// If the condition is false, throw a fatal error
void Flow_Assert(int condition, const char* errorMsg){
    if (!condition){
        Flow_FatalError(errorMsg);
    }
}






// ---------------------------------------------------------------------------- Memory Functions

// **************************************************************************** Memory_Allocate

// Allocate a memory block at ptr and set all the values to 0
void* Memory_Allocate(void* ptr, int size){
    if (ptr == NULL){
        ptr = malloc(size);
    }else{
        ptr = realloc(ptr, size);
    }

    Flow_Assert(ptr != NULL, "Failed to allocate memory");

    Memory_Set(ptr, size, 0);

    return ptr;
}


// **************************************************************************** Memory_Copy

// Copy the memory block from src to dst
void* Memory_Copy(void* dst, const void* src, int size){
    if (dst != src){
        dst = Memory_Allocate(dst, size);
        Memory_Write(dst, src, size);
    }

    return dst;
}


// **************************************************************************** Memory_Write

// Copy the memory block from src to dst, blindly, without allocating memory
void Memory_Write(void* dst, const void* src, int size){
    for (int i = 0; i < size; i++){
        *((unsigned char*) dst + i) = *((unsigned char*) src + i);
    }
}


// **************************************************************************** Memory_Set

// Set all the values of the memory block
void Memory_Set(void* ptr, int size, unsigned char value){
    for (int i = 0; i < size; i++){
        *((unsigned char*) ptr + i) = value;
    }
}


// **************************************************************************** Memory_Free

// Free the memory at ptr. Return NULL
void* Memory_Free(void* ptr){
    if (ptr != NULL){
        free(ptr);
    }

    return NULL;
}


// **************************************************************************** Memory_FreeAll

// Free the memory at all the given pointers. The arguments must be in the form 
// of pointers to pointers (void**), so that they can be set to NULL
void Memory_FreeAll(int nObjects, ...){
    if (nObjects <= 0) {return;}

    va_list argPtr;

    va_start(argPtr, nObjects);
    for (int i = 0; i < nObjects; i++){
        void** temp = va_arg(argPtr, void**);
        if (temp == NULL) {continue;}
        *temp = Memory_Free(*temp);
    }
    va_end(argPtr);
}

