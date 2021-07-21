#include "Execute.h"

#include <AMPLE.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/**
 * Flag to check if Execute module has been initialized
 */
static bool Initialized = false;

/**
 * Flag to check if Execute module has been cleaned up
 */
static bool HasCleanUp = false;


static AMPLE_BIN* Program = NULL;
static AMPLE_INSTRUCTION* ProgramInstructions = NULL;


INLINE void ConvertU32(uint32_t* val) {
	*val = ConvertEndianU32(*val);
}

INLINE void ConvertU64(uint64_t* val) {
	*val = ConvertEndianU64(*val);
}

bool ExecuteInitialize() {
	if (Initialized)
		return true;

	HasCleanUp = false;
	Initialized = true;

	return true;
}


bool ExecuteExecute(uint8_t* programBytes, int64_t programSize, uint64_t programCounter) {
	if (!Initialized || HasCleanUp || (programSize < 64))
		return false;

	Program = (AMPLE_BIN*)programBytes;

	/**
	 * Check Magic Number to make sure it is correct
	 * and return false if it isn't, or if endianess 
	 * not detected
	 */
	uint8_t computerEndian = GetEndianness();
	uint8_t programEndian = VOODOO_ENDIAN_D;
	if (computerEndian == LITTLE_ENDIAN_D) {
		if (Program->AMPLE_MAGIC == 24016930118585665)
			programEndian = LITTLE_ENDIAN_D;
		else if (Program->AMPLE_MAGIC == 4705505474182862080)
			programEndian = BIG_ENDIAN_D;
		else {
			fprintf(stderr, "Program passed is not AMPLE\n");
			return false;
		}
	}
	else if ((computerEndian == BIG_ENDIAN_D) && (Program->AMPLE_MAGIC != 4705505474182862080)) {
		if (Program->AMPLE_MAGIC == 24016930118585665)
			programEndian = BIG_ENDIAN_D;
		else if (Program->AMPLE_MAGIC == 4705505474182862080)
			programEndian = LITTLE_ENDIAN_D;
		else {
			printf("Program passed is not AMPLE\n");
			return false;
		}
	}
	else if (computerEndian == VOODOO_ENDIAN_D) {
		fprintf(stderr, "Unknown endianness. AMPLE can only run on a big and little endian systems\n");
		return false;
	}

	if (computerEndian != programEndian) {
		ConvertU64(&Program->AMPLE_MAGIC);
		ConvertU64(&Program->AMPLE_BIN_STRUCT_VERSION);
		ConvertU64(&Program->AMPLE_INITIAL_VERSION);
		ConvertU64(&Program->AMPLE_MIN_MEMORY);
		ConvertU64(&Program->AMPLE_TABLE_CONTENT);
		ConvertU64(&Program->AMPLE_NUM_OF_TABLE_CONTENT);
		ConvertU64(&Program->AMPLE_TABLE_OF_INSTRUCTIONS);
		ConvertU64(&Program->AMPLE_NUM_OF_INSTRUCTIONS);
	}

	printf("Endianness: %s\nMagic Number: %llu\nBin Version: %llu\nInitial Version: %llu\nMin Memory: %llu\nContents: %llu\nNumber of contents: %llu\nInstructions: %llu\nNumber of instructions: %llu\n\n",
	            (programEndian == LITTLE_ENDIAN_D) ? "Little" : "Big",
				Program->AMPLE_MAGIC,
				Program->AMPLE_BIN_STRUCT_VERSION,
				Program->AMPLE_INITIAL_VERSION,
				Program->AMPLE_MIN_MEMORY,
				Program->AMPLE_TABLE_CONTENT,
				Program->AMPLE_NUM_OF_TABLE_CONTENT,
				Program->AMPLE_TABLE_OF_INSTRUCTIONS,
				Program->AMPLE_NUM_OF_INSTRUCTIONS);

	if (Program->AMPLE_TABLE_OF_INSTRUCTIONS + Program->AMPLE_NUM_OF_INSTRUCTIONS * sizeof(AMPLE_INSTRUCTION) >= programSize) {
		fprintf(stderr, "Program contains an error in its program table\n");
		return false;
	}

	ProgramInstructions = (AMPLE_INSTRUCTION*)(&(programBytes[Program->AMPLE_TABLE_OF_INSTRUCTIONS]));


	if (computerEndian != programEndian)
		for (int64_t i = 0; i < Program->AMPLE_NUM_OF_INSTRUCTIONS; i++) {
			ConvertU32(&ProgramInstructions[i].INSTRUCTION);
			ConvertU32(&ProgramInstructions[i].MODE);
			ConvertU64(&ProgramInstructions[i].ARG1);
			ConvertU64(&ProgramInstructions[i].ARG2);
			ConvertU64(&ProgramInstructions[i].ARG3);
		}
	for (int64_t i = 0; i < Program->AMPLE_NUM_OF_INSTRUCTIONS; i++) {
		printf("OP Code: %u\nMode: %u\nArg1: %llu\nArg2: %llu\nArg3: %llu\n\n",
		       ProgramInstructions[i].INSTRUCTION,
		       ProgramInstructions[i].MODE,
		       ProgramInstructions[i].ARG1,
		       ProgramInstructions[i].ARG2,
		       ProgramInstructions[i].ARG3);
	}

	return true;
}


void ExecuteCleanUp() {
	if (HasCleanUp)
		return;

	Program = NULL;
	ProgramInstructions = NULL;

	Initialized = false;
	HasCleanUp = true;
}