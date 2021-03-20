#include "AMPLE.h"

#include "File.h"

#include <stdint.h>
#if defined(__GNUC__)
    #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"

typedef struct
{
    char* fname;
    int64_t fnameLength;
    uint8_t mode;
    bool open;
    FILE* fptr;
    uint64_t position;
} FileStruct;

FileStruct* openFiles = NULL;
uint64_t openFilesCount = 0;
uint64_t openFilesSize = 0;

/**
 * Double the size of the openFiles array and openFilesCount
 * @return true if successful and false if not
 */
static bool DoubleOpenFiles() {
	if (!openFiles)
		return false;

	uint64_t newSize = 2 * openFilesCount;
	FileStruct* newOpenFiles = (FileStruct*)realloc(openFiles, newSize * sizeof(FileStruct));
	if (!newOpenFiles)
		return false;

	openFiles = newOpenFiles;
	openFilesCount = newSize;

	return true;
}

static FILE* openFile(const char* fname, uint8_t mode) {
	char fmode[4] = { 0x00, 0x00, 0x00, 0x00 };
	uint8_t bcounter = 0;
	if (mode & NFILE_WRITE)
		fmode[bcounter++] = 'w';
	else if (mode & NFILE_READ)
		fmode[bcounter++] = 'r';
	else
		fmode[bcounter++] = 0x00;

	if (mode & NFILE_APPEND)
		fmode[bcounter++] = 'a';
	if (mode & NFILE_BINARY)
		fmode[bcounter] = 'b';

	FILE* fptr;
#if defined(__WINDOWS__)
	fopen_s(&fptr, fname, fmode);
#elif defined(__LINUX__) || defined(__APPLE__)
	fptr = fopen(fname, fmode);
#endif

	return fptr;
}


bool NFileInitialize() {
	if (openFiles)
		return true;

	openFilesCount = 1;
	openFiles = (FileStruct*)malloc(openFilesCount * sizeof(FileStruct));
	return openFiles;
}


bool NFileExists(const char* fname) {
	if (!openFiles)
		return false;
	FILE* fptr = openFile(fname, NFILE_READ);
	if (!fptr)
		return false;
	fclose(fptr);
	return true;
}


NFILE NFileOpen(const char* fname, uint8_t mode) {
	if (!openFiles)
		return false;

	FILE* fptr = openFile(fname, mode);
	if (!fptr)
		return false;

	FileStruct* fs = (FileStruct*)malloc(sizeof(FileStruct));
	if (!fs) {
		fclose(fptr);
		return false;
	}

	fs->fnameLength = strlen(fname);
	fs->fname = (char*)malloc((fs->fnameLength + 1) * sizeof(char));
	if (!fs->fname) {
		fclose(fptr);
		free(fs);
		return false;
	}
	memcpy(fs->fname, fname, (fs->fnameLength + 1) * sizeof(char));

	fs->mode = mode;
	fs->open = true;
	fs->fptr = fptr;
	fs->position = 0;

	if ((openFilesSize >= openFilesCount) && !DoubleOpenFiles()) {
		fclose(fptr);
		free(fs->fname);
		free(fs);
		return false;
	}
	openFiles[openFilesSize] = *fs;

	return &(openFiles[openFilesSize++]);

}

void NFileClose(NFILE file) {
	FileStruct* fs = (FileStruct*)file;
	if (!openFiles || !fs || !fs->open)
		return;

	fclose(fs->fptr);
}


FILE* NFileGetCFILE(NFILE file) {
	if (!openFiles || !file)
		return (FILE*)NULL;

	FileStruct* fs = (FileStruct*)file;
	return (fs->open) ? fs->fptr : (FILE*)NULL;
}


int64_t NFileGetFileSize(NFILE file) {
	FileStruct* fs = (FileStruct*)file;
	if (!openFiles || !fs || !fs->open)
		return -1;

	int64_t size = -1;

#if defined(__WINDOWS__)
	_fseeki64(fs->fptr, 0L, SEEK_END);
	size = _ftelli64(fs->fptr);
	_fseeki64(fs->fptr, 0L, SEEK_SET);
#elif defined(__LINUX__) || defined(__APPLE__)
	fseeko(fs->fptr, 0L, SEEK_END);
	size = ftello(fs->fptr);
	fseeko(fs->fptr, 0L, SEEK_SET);
#endif

	return size;
}

int64_t NFileReadFile(NFILE file, void* destination, int64_t destinationSize) {
	FileStruct* fs = (FileStruct*)file;
	if (!openFiles || !fs || !fs->open)
		return -1;

	int64_t change = fread(destination, destinationSize, destinationSize, fs->fptr);
	fs->position += change;
	return change;
}

int64_t NFileWriteFile(NFILE file, void* source, int64_t sourceSize) {
	FileStruct* fs = (FileStruct*)file;
	if (!openFiles || !fs || !fs->open)
		return -1;

	int64_t change = fwrite(source, sourceSize, sourceSize, fs->fptr);
	fs->position += change;
	return change;
}


void NFileCloseAllFiles() {
	if (!openFiles)
		return;

	for (int64_t i = 0; i < openFilesSize; i++) {
		FileStruct fs = openFiles[i];

		// Check if the file is open and if yes, close it and set the pointer to NULL
		if (fs.open) {
			fclose(fs.fptr);
			fs.fptr = (FILE*)NULL;
			fs.open = false;
		}

		// Check if the file name is set and if it is free it and set the pointer to NULL
		if (fs.fname) {
			free(fs.fname);
			fs.fname = (char*)NULL;
			fs.fnameLength = 0;
		}
	}
	openFilesSize = 0;
}

void NFileCleanUp() {
	if (!openFiles)
		return;

	NFileCloseAllFiles();

	openFilesCount = 0;
	free(openFiles);
	openFiles = (FileStruct*)NULL;

}
