#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define NFILE_READ 0x01
#define NFILE_WRITE 0x02
#define NFILE_APPEND 0x04
#define NFILE_BINARY 0x08

#define NFILE void*

/**
 * Initializes the NFile Library
 * Without it the rest of the library will always fail
 * @return true if successful or false if not successful
 */
bool NFileInitialize();

/**
 * Checks if a file with that name exists or not
 * @param fname The file name to check
 * @return true if it exists and false if not
 */
bool NFileExists(const char* fname);

/**
 * Opens file with name and mode passed
 * @param fname The file name to open
 * @param mode The mode can be a mix of READ, WRITE, APPEND, BINARY
 * @return The pointer if successful or NULL on failure
 */
NFILE NFileOpen(const char* fname, uint8_t mode);
/**
 * Closes an previously opened file
 * @param file The file pointer created by NFileOpen
 */
void NFileClose(NFILE file);

/**
 * Get the C FILE* for a normal C program use. Note that if changes are made to it
 * like fclose then the library will malfunction
 * @param file The file pointer created by NFileOpen
 * @return The FILE* pointer or NULL if file closed or does not exist
 */
FILE* NFILEGetCFILE(NFILE file);

/**
 * Get the 64 bit file size.
 * @param file The file pointer created by NFileOPen
 * @return The positive 64 bit length if successful or -1 if not successful
 */
int64_t NFileGetFileSize(NFILE file);
/**
 * Read bytes from file to array pointer
 * @param file The file pointer created by NFileOpen
 * @param destination The destination pointer
 * @param destinationSize The length of the destination pointer
 * @return The positive 64 bit length if successful or -1 if not successful
 */
int64_t NFileReadFile(NFILE file, void* destination, int64_t destinationSize);
/**
 * Write bytes from file to array pointer
 * @param file The file pointer created by NFileOpen
 * @param source The source pointer
 * @param sourceSize The length of the source pointer
 * @return The positive 64 bit length if successful or -1 if not successful
 */
int64_t NFileWriteFile(NFILE file, void* source, int64_t sourceSize);

/**
 * Closes all the files opened by NFileOpen
 * Note that the previously opened files can not be used.
 */
void NFileCloseAllFiles();

/**
 * De initialize the NFile Library
 */
void NFileCleanUp();

#ifdef __cplusplus
}
#endif