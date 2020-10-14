#pragma once

#include <stdbool.h>
#include <stdint.h>

#define FILE_READ 0b0
#define FILE_WRITE 0b1
#define FILE_APPEND 0b10
#define FILE_BINARY 0b100

bool FileExists(const char* fname);

void* FileOpen(const char* fname, uint8_t mode);