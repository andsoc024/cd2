// ============================================================================
// CD2
// File
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ INFO
/*
    Functions for file management.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <dirent.h>

#include "Fund.h"


// ============================================================================ PRIVATE CONSTANTS

#define DEF_PATH_LENGTH                     700


// ============================================================================ PRIVATE FUNC DECL

void            Path_GetHomeDir_NS(char* dst, int maxLength);


// ============================================================================ FUNC DEF

// ---------------------------------------------------------------------------- Path Functions

// **************************************************************************** Path_GetHomeDir

// Get the path of the home directory
char* Path_GetHomeDir(char* dst){
    char* homeDirPath = Memory_Allocate(NULL, DEF_PATH_LENGTH);
    Path_GetHomeDir_NS(homeDirPath, DEF_PATH_LENGTH);
    Flow_Assert(*homeDirPath != '\0', "Failed to get the home directory path");
    Flow_Assert(File_DirExists(homeDirPath), "Home Directory could not be found");

    dst = String_Copy(dst, homeDirPath);

    homeDirPath = Memory_Free(homeDirPath);

    return dst;
}


// **************************************************************************** Path_Append

// Add the component to the path
char* Path_Append(char* path, const char* pathComp){
    int pathLength = String_Length(path);
    const char* sep = (*(path + pathLength - 1) == '/') ? "" : "/";
    if (pathComp != NULL && *pathComp != '\0'){
        path = String_Concat(path, 3, path, sep, pathComp);
    }

    return path;
}






// ---------------------------------------------------------------------------- File Functions

// **************************************************************************** File_ReadStringFromFile

// Read the conetnts of the file as a string. Save it at dst
char* File_ReadStringFromFile(char* dst, FILE* file){
    char* temp = Memory_Allocate(NULL, DEF_PATH_LENGTH);
    char* ptr = temp;

    int count = 0;
    for (int chr = 0; (chr = fgetc(file)) != EOF; ptr++){
        if (chr == '\n') {continue;}
        *ptr = chr;
        count++;
        if (count >= DEF_PATH_LENGTH - 1){
            break;
        }
    }
    *ptr = '\0';

    dst = String_Copy(dst, temp);

    temp = Memory_Free(temp);

    return dst;
}


// **************************************************************************** File_Exists

// Return true if the file exists
bool File_Exists(const char* path){
    FILE* file = fopen(path, "r");

    if (file == NULL){
        return false;
    }

    fclose(file);
    return true;
}


// **************************************************************************** File_DirExists

// Return true if the folder exists
bool File_DirExists(const char* path){
    DIR* dir = opendir(path);

    if (dir == NULL){
        return false;
    }

    closedir(dir);
    return true;
}


// **************************************************************************** File_Delete

// Delete the file. Return true if succesful
bool File_Delete(const char* path){
    if (!File_Exists(path)){
        return true;
    }

    char* command = String_Copy(NULL, path);
    command = String_PutInQuotes(command, "\"");
    command = String_Concat(command, 2, "rm ", command);
    system(command);
    command = Memory_Free(command);

    return !File_Exists(path);
}



