#ifndef __AMPLE_LIBRARY_AMPLE_EXPORT_IMPORT_H__
#define __AMPLE_LIBRARY_AMPLE_EXPORT_IMPORT_H__

#include "OS Detection.h"

#if defined(__WINDOWS__)
    #define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif defined(__LINUX__) || defined(__APPLE__)
    #define EXPORT __attribute__((visibility("default")))
	#define IMPORT
#endif

#endif//__AMPLE_LIBRARY_AMPLE_EXPORT_IMPORT_H__