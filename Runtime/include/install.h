#pragma once

#if defined(__WITH_INSTALL__)

#include <stdbool.h>
#include <stdint.h>

#define LIBRARY 0x01
#define RUNTIME 0x02

bool Download(uint8_t type, const char* name, const char* url);

#endif