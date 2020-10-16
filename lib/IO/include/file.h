#pragma once

#include <stdbool.h>
#include <stdint.h>

#define FILE_READ 0x00
#define FILE_WRITE 0x01
#define FILE_APPEND 0x02
#define FILE_BINARY 0x04

bool FileExists(const char* fname);

void* FileOpen(const char* fname, uint8_t mode);