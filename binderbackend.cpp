//==============================================================================

							         	/* binderbackend.cpp */

//==============================================================================
#include "codearray.h" // source of our executables.
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<windows.h>

//==============================================================================
void spawnProcess(char* progName)
{
  /*
    CreateProcess(...) is the closest substitue for linux fork() I found.
		I found it here:
    https://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx
  */
  STARTUPINFO si; // Pointer to STARTUPINFO structure
  PROCESS_INFORMATION pi; // Pointer to PROCESS_INFORMATION structure

  ZeroMemory( &si, sizeof(si) ); // initialize to empty memory, e.g. NULL
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) ); // same ^

  // Start the new process.
    if( !CreateProcess( NULL, progName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
      printf( "CreateProcess failed (%d).\n", GetLastError() );
    }
    else
    {
      printf("Starting Program: %s", programName);
    }
}
//==============================================================================

													       /* Main */

//==============================================================================
int main()
{
	// Go through the binaries found in the header file
	for(int progIndex = 0; 	progIndex < NUM_BINARIES; ++progIndex)
	{
		// Create a temporary file you can use the tmpnam() function for this.
		// "If the argument is NULL, this name is generated in an internal static buffer and may be overwritten by the next call to tmpnam()" Is this what we want?
		char* progName = tmpnam(NULL);

		// Create a file with the name generated by tmpnam.
		FILE* progFile = fopen(progName, "w");

		// These bytes are found in codeArray[progIndex] in the header file.
		// Write the bytes of the first program to the file.
		for(int byteIndex = 0; byteIndex < progLens[progIndex]; byteIndex++)
		{
			fputc(codeArray[progIndex][byteIndex], progFile);
		}

		// close the file, we are done writing to it.
		fclose(progFile);

		// create a process for this executable.
		spawnProcess(progName);
	}
	return 0;
}
//==============================================================================
