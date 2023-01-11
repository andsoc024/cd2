// ============================================================================
// CD2
// Script Header
// by Andreas Socratous
// Jan 2023
// ============================================================================


#ifndef SCRIPT_GUARD
#define SCRIPT_GUARD


// ============================================================================ INFO
/*
    Format apple script commands as one line shell command.
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// ============================================================================ FUNC DECL

char*           Script_FormatAsOneLineShellCommand(char* dst, int nCommands, ...);



#endif // SCRIPT_GUARD

