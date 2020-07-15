#include "Program.h"

#include "DllNotFoundException.h"
#include "File.h"
#include "IOException.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"
#include "MissingMethodException.h"
#include "CorruptedProgramException.h"
#include "OutOfMemoryException.h"

#include "opcodes/Hlt.h"
#include "opcodes/Mov.h"

#include <cmath>
#include <cstdio>
#include <ctime>
#include <exception>
#include <map>

int exitCode = 0;

inline bool GetBit(uint8_t byte, uint8_t bitPossition)
{
    return (byte >> bitPossition) & 1;
}

template<typename T>
inline T fixBytes(T value)
{
    size_t sizeofT = sizeof(T);
    uint8_t returnVal[sizeofT];
    for (uint32_t i = 0; i < sizeofT; i++)
        returnVal[i] = ((uint8_t*)&value)[sizeofT - i - 1];
    return *(T*)returnVal;
}

std::vector<uint8_t*> Program::GetProgram(FILE *fptr)
{
    auto returnVal = std::vector<uint8_t*>();

    fpos_t position;
    fgetpos(fptr, &position);
    size_t startOfProgram = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    size_t endOfProgram = ftell(fptr);
    fsetpos(fptr, &position);
    size_t sizeOfProgram = endOfProgram - startOfProgram;

    if (sizeOfProgram % (Program::matrixColumns * Program::matrixRows) != 0)
        throw CorruptedProgramException("Program is corrupted 1");

    int numOfInstr = int((sizeOfProgram * 1.0) / ((Program::matrixColumns) * (Program::matrixRows)));

    for (int i = 0; i < numOfInstr; i++)
    {
        auto instruction = (uint8_t*)malloc(matrixRows * matrixColumns * sizeof(uint8_t));
        for (int j = 0; j < matrixRows * matrixColumns; j++)
        {
            int data = fgetc(fptr);
            if (data == -1)
                throw CorruptedProgramException("Program is corrupted 2");
            instruction[j] = (uint8_t)data;
        }
        returnVal.push_back(instruction);
    }

    return returnVal;
}

void Program::Main(std::vector<std::string>& args)
{
    clock_t startTime = clock();
    if (args.empty())
    {
        fprintf(stderr, "You need to specify program files to run.\n");
        exit(-1);
    }

    if (args.size() == 1)
    {
        if ((args[0] == std::string("-h")) || (args[0] == std::string("--help")))
        {
            fprintf(stdout, "AMPLE VM\nSupports AMPLE V1\nExperimental Features\n");
            exit(0);
        }
        else if ((args[0] == std::string("-v")) || (args[0] == std::string("--version")))
        {
            fprintf(stdout, "AMPLE VM Version: Alpha 0.1\nExperimental Features\n");
            exit(0);
        }
    }

    if (args.size() > 1 && (args[0] == std::string("-i") || args[0] == std::string("--install")))
    {
        args.erase(args.begin());
        if (!Library::InstallLibraries(args)) exit(-1);
        exit(0);
    }

    for (auto& fileName : args)
    {
        if ((fileName.find_last_of('.') != std::string::npos) ? fileName.substr(fileName.find_last_of('.') + 1) != std::string("ample"): true)
        {
            fprintf(stderr, "File: \"%s\" is not an AMPLE Executable File\n", fileName.c_str());
            exit(-1);
        }
        FILE* fptr;
        try
        {
            fptr = File::Open(fileName, FileMode::Read);
        }
        catch (IOException& e)
        {
            fprintf(stderr, "%s", e.what());
            exit(-1);
        }

        auto Libraries = new std::map<int, std::pair<Library*, std::map<int, void*>>>();
        auto Variables = new std::map<std::string, std::string>();
        Memory* memory = (Memory*)malloc(sizeof(Memory));
        Memory* registers = (Memory*)malloc(sizeof(Memory));

        try {
            LoadMetaData(fptr, *Libraries, *Variables);

            uint64_t memorySize = 1024;
            if (Variables->find("Memory") != Variables->end())
            {
                bool memorySet = false;
                if (((*Variables)["Memory"]).size() > 2)
                {
                    std::string& memSetting = (*Variables)["Memory"];
                    if (memSetting.substr(memSetting.size() - 2) == "KB")
                    {
                        std::string bb = memSetting.substr(0, memSetting.size() - 2);
                        memorySize = std::stoull(bb) * 1024;
                        memorySet = true;
                    }
                    else if (memSetting.substr(memSetting.size() - 2) == "MB")
                    {
                        std::string bb = memSetting.substr(0, memSetting.size() - 2);
                        memorySize = std::stoull(bb) * 1024 * 1024;
                        memorySet = true;
                    }
                    else if (memSetting.substr(memSetting.size() - 2) == "GB")
                    {
                        std::string bb = memSetting.substr(0, memSetting.size() - 2);
                        memorySize = std::stoull(bb) * 1024 * 1024 * 1024;
                        memorySet = true;
                    }
                    else if (memSetting.substr(memSetting.size() - 2) == "TB")
                    {
                        std::string bb = memSetting.substr(0, memSetting.size() - 2);
                        memorySize = std::stoull(bb) * 1024 * 1024 * 1024 * 1024;
                        memorySet = true;
                    }
                }
                try {
                    if (!memorySet)
                        memorySize = std::stoull((*Variables)["Memory"]);
                }
                catch (...) { }
            }

            if (!(MemoryInit(&memory, memorySize, 1) && MemoryInit(&registers, 64, 8)))
                throw OutOfMemoryException("Out of Memory");

            std::vector<uint8_t*> program = Program::GetProgram(fptr);

            for (uint32_t j = 0; j < (uint32_t)program.size(); j++) {
                uint8_t* i = program[j];
                if (GetBit(i[0], 7) == 1)
                {
                    uint8_t f = i[0];
                    f &= ~(1UL << 7);
                    unsigned int classPos = ((int)f) << 24 | ((int)i[1]) << 16 | ((int)i[2]) << 8 | ((int)i[3]);
                    unsigned int functionPos = ((int)i[4]) << 24 | ((int)i[5]) << 16 | ((int)i[6]) << 8 | ((int)i[7]);
                    if ((*Libraries).find(classPos) == (*Libraries).end())
                        throw DllNotFoundException("Class not found");
                    if ((*Libraries)[classPos].second.find(functionPos) == (*Libraries)[classPos].second.end())
                        throw MissingMethodException("Method not found");
                    auto function = (void (*)(void *, void *)) (*Libraries)[classPos].second[functionPos];
                    function(memory, registers);
                }
                else
                {
                    uint32_t functionNum = fixBytes<uint32_t>(*(uint32_t*)i);
                    i += 4;
                    uint32_t modeNum = fixBytes<uint32_t>(*(uint32_t*)i);
                    i += 4;
                    uint64_t arg1 = fixBytes<uint64_t>(*(uint64_t*)i);
                    i += 8;
                    uint64_t arg2 = fixBytes<uint64_t>(*(uint64_t*)i);
                    i += 8;
                    uint64_t arg3 = fixBytes<uint64_t>(*(uint64_t*)i);
                    switch (functionNum)
                    {
                        case 0x00: //Stall (Do nothing)
                            HltOP(modeNum, arg1, arg2, arg3, memory, registers, &j);
                            break;

                        case 0x01: // mov(00000001)
                            MovOP(modeNum, arg1, arg2, arg3, memory, registers, &j);
                            break;

                        case 0x02: // jmp to next 4 bytes
                        {
                            j = (((int)i[4]) << 24 | ((int)i[5]) << 16 | ((int)i[6]) << 8 | ((int)i[7])) - 1;
                        }
                        break;

                        default:
                        {
                            throw MissingMethodException("Method not found");
                        }
                    }
                }
            }

            for (auto& i : program)
                free(i);
        }
        catch (std::exception& e)
        {
            FreeMemory(memory);
            FreeMemory(registers);
            free(memory);
            free(registers);
            fflush(stdout);
            fflush(stderr);
            fprintf(stderr, "%s\n", e.what());
            exitCode = -1;
        }

        FreeMemory(memory);
        FreeMemory(registers);

        for (auto& Library : *Libraries)
            delete Library.second.first;

        delete Libraries;
        delete Variables;

        fclose(fptr);
    }

    clock_t endTime = clock();
    double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    exit(exitCode);
}
