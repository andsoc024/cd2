// ============================================================================
// CD2
// Home Directory
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ INFO
/*
    Objective C function for determining the home directory.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <Cocoa/Cocoa.h>


// ============================================================================ FUNC DEF

// **************************************************************************** Path_GetHomeDir_NS

// Objective C function for determining the home directory
void Path_GetHomeDir_NS(char* dst, int maxLength){
    NSString* homeDir = NSHomeDirectory();
    const char* cStr = [homeDir UTF8String];

    char* ptr = dst;

    int count = 0;
    for (; *cStr != '\0'; cStr++, ptr++, count++){
        *ptr = *cStr;
        if (count >= maxLength){
            *dst = '\0';
            [homeDir release];
            return;
        }
    }

    *ptr = '\0';

    [homeDir release];
}


