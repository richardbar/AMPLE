#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define FILE_READ 0x01
#define FILE_WRITE 0x02
#define FILE_APPEND 0x04
#define FILE_BINARY 0x08

#define NFILE int64_t

bool NFileExists(const char* fname);

NFILE NFileOpen(const char* fname, uint8_t mode);
void NFileClose(NFILE* file);

int64_t NGetFileSize(NFILE file);
int64_t NReadWholeFile(NFILE file, void* destination, int64_t destionationSize);
int64_t NReadFile(NFILE file, void* destionation, int64_t destionationSize, int64_t length);

void FCloseAllFiles();

#ifdef __cplusplus
}
#endif