// ============================================================================
// CD2
// Main
// by Andreas Socratous
// Jan 2023
// ============================================================================


// ============================================================================ 
#define APP_VERSION                         "1.0.0"

//#define DEBUG_MODE


// ============================================================================ INFO
/*
    The program opens a new terminal window at the path of the active window of 
    the Finder:
    1) Get the path of the active Finder window, using apple script
    2) Store it in a temporary file at the home folder
    3) Read the path from the temporary file
    4) Delete the temporary file
    5) Use apple script again to open a Terminal window at the given path
*/


// ============================================================================ DEPENDENCIES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Mods/Fund/Fund.h"
#include "Mods/Script/Script.h"

#ifdef DEBUG_MODE
    #include "Test.c"
#endif


// ============================================================================ CONSTANTS

#define TEMP_FILE_NAME                      ".andsoc_cd2_temp"
#define READ_FILE_ATTEMPTS_N                10000

#define AS_COM_EXPORT_ACTIVE_FOLDER_PATH \
    "tell application \"Finder\" to set myname to POSIX path of (target of window 1 as alias)"

#define AS_COM_CHANGE_TERMINAL_DIR \
    "do script \"cd \\\"<FOLDER_PATH>\\\"\""


// ============================================================================ MAIN

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv){

    #ifdef DEBUG_MODE
        return Test(argc, argv);
    #endif

    char* tempFilePath = NULL;            // The temporary file where the active folder path is saved
    FILE* tempFile = NULL;
    char* activeFolderPath = NULL;        // The path of the active Finder window
    char* sCommand = NULL;                // Shell command for executing one or more apple script commands


    // ........................................................................
    // Determine the path of the temp file
    // ........................................................................
    tempFilePath = Path_GetHomeDir(NULL);
    tempFilePath = Path_Append(tempFilePath, TEMP_FILE_NAME);


    // ........................................................................
    // Export the active folder path in the temporary file
    // ........................................................................
    // tell application "Finder" to set myname to POSIX path of (target of window 1 as alias)
    sCommand = String_Copy(NULL, AS_COM_EXPORT_ACTIVE_FOLDER_PATH);
    // 'tell application "Finder" to set myname to POSIX path of (target of window 1 as alias)'
    sCommand = String_PutInQuotes(sCommand, "'");
    // osascript >"<FILE>" -e 'tell application "Finder" to set myname to POSIX path of (target of window 1 as alias)'
    sCommand = String_Concat(sCommand, 2, "osascript >\"<FILE>\" -e ", sCommand);
    sCommand = String_Replace(sCommand, "<FILE>", tempFilePath);
    system(sCommand);
    

    // ........................................................................
    // Read the path from the temp file
    // ........................................................................
    // Open the file
    int count = 0;
    while ((tempFile = fopen(tempFilePath, "r")) == NULL){
        count++;
        Flow_Assert(count < READ_FILE_ATTEMPTS_N, "Could not find the temporary file");
    }

    // Read the active folder path
    activeFolderPath = File_ReadStringFromFile(NULL, tempFile);
    Flow_Assert(File_DirExists(activeFolderPath), "Could not find the active Finder directory");

    // Delete the temporary file
    fclose(tempFile);
    File_Delete(tempFilePath);


    // ........................................................................
    // Construct Apple Script commands for opening the terminal at the active 
    // folder
    // ........................................................................

    // tell application "Terminal"
    //    activate
    //    do script "cd \"FOLDER_PATH\""
    // end tell

    const char* asCommand1 = "tell application \"Terminal\"";

    const char* asCommand2 = "activate";

    char* asCommand3 = String_Copy(NULL, AS_COM_CHANGE_TERMINAL_DIR);
    asCommand3 = String_Replace(asCommand3, "<FOLDER_PATH>", activeFolderPath);

    const char* asCommand4 = "end tell";


    // ........................................................................
    // Combine the 4 Apple Script commands into a one line shell command in 
    // the form: osascript -e 'COMMAND1' -e 'COMMAND2' ...
    // ........................................................................
    sCommand = Script_FormatAsOneLineShellCommand(sCommand, 4, asCommand1, asCommand2, asCommand3, asCommand4);
    
    // Execute the command
    system(sCommand);

    // ........................................................................
    // Clean Up
    // ........................................................................
    Memory_FreeAll(4, &sCommand, &tempFilePath, &activeFolderPath, &asCommand3);

    return 0;
}

