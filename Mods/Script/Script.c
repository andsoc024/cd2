// ============================================================================
// CD2
// Script
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ INFO
/*
    Functions for formatting apple script commands as shell commands.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdarg.h>

#include "../Fund/Fund.h"


// ============================================================================ PRIVATE FUNC DECL

char*           FormatSingleCommand(char* dst, const char* asCommand);






// ============================================================================ FUNC DEF

// **************************************************************************** Script_FormatAsOneLineShellCommand

// Format the apple script commands as a single line shell command in the form: 
// osascript -e 'COMMAND1' -e 'COMMAND2' ...
char* Script_FormatAsOneLineShellCommand(char* dst, int nCommands, ...){ 
    if (nCommands <= 0){
        return Memory_Free(dst);
    }

    dst = String_Copy(dst, "osascript");

    va_list argPtr;

    va_start(argPtr, nCommands);
    for (int i = 0; i < nCommands; i++){
        const char* asCommand = va_arg(argPtr, char*);
        if (asCommand == NULL) {continue;}

        char* sCommand = FormatSingleCommand(NULL, asCommand);

        dst = String_Concat(dst, 2, dst, sCommand);

        sCommand = Memory_Free(sCommand);
    }
    va_end(argPtr);

    return dst;
}






// ============================================================================ PRIVATE FUNC DEF

// **************************************************************************** FormatSingleCommand

// Format the apple script command as a component for a single line shell 
// command in the form: -e 'COMMAND'
char* FormatSingleCommand(char* dst, const char* asCommand){
    dst = String_Copy(dst, asCommand);
    dst = String_PutInQuotes(dst, "'");
    dst = String_Concat(dst, 2, " -e ", dst);
    return dst;
}

