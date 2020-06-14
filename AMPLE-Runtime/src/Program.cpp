#include "Program.h"

#include "DllNotFoundException.h"
#include "File.h"
#include "IOException.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"
#include "MissingMethodException.h"
#include "CorruptedProgramException.h"
#include "Register.h"

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
        Memory* memory = {nullptr};
        Register* registers = {nullptr};

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

            memory = new Memory(memorySize);
            registers = new Register(64);

            std::vector<uint8_t*> program = Program::GetProgram(fptr);

            for (long j = 0; j < (long)program.size(); j++) {
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
                    unsigned int functionNum = 0;
                    for (int k = 0; k < 4; k++)
                    {
                        functionNum += ((int)i[k]) << (24 - 8 * k);
                    }
                    switch (functionNum)
                    {
                        case 0x00: //Stall (Do nothing)
                        break;

                        case 0x01: // mov(00000001)
                        {
                            uint64_t operationType = 0;
                            for (int k = 0; k < 8; k++)
                                operationType += (uint64_t)i[4 + k] << (56 - 8 * k);
                            switch (operationType)
                            {
                                case 0x00: //mov r1, $1 // 1 -> r1 (000000010000000000000000)
                                {
                                    uint64_t registerNum = 0;
                                    int64_t value = 0;
                                    for (int k = 0; k < 8; k++)
                                        registerNum += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        value += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)registers->Get(registerNum)) = value;
                                }
                                break;

                                case 0x01: //mov r1, r2 // r2 -> r1 (000000010000000000000001)
                                {
                                    uint64_t registerNum1 = 0;
                                    int64_t registerNum2 = 0;
                                    for (int k = 0; k < 8; k++)
                                        registerNum1 += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        registerNum2 += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)registers->Get(registerNum1)) = *((int64_t*)registers->Get(registerNum2));
                                }
                                break;

                                case 0x02: //mov r1, m1 // m1 -> r1 (000000010000000000000002)
                                {
                                    uint64_t registerNum = 0;
                                    int64_t memoryNum = 0;
                                    for (int k = 0; k < 8; k++)
                                        registerNum += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        memoryNum += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)registers->Get(registerNum)) = *((int64_t*)memory->Get(memoryNum));
                                }
                                break;

                                case 0x03: //mov m1, $1 // 1 -> m1 (000000010000000000000003)
                                {
                                    uint64_t memoryNum = 0;
                                    int64_t value = 0;
                                    for (int k = 0; k < 8; k++)
                                        memoryNum += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        value += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)memory->Get(memoryNum)) = value;
                                }
                                break;

                                case 0x04: //mov m1, m2 // m2 -> m1 (000000010000000000000004)
                                {
                                    uint64_t memoryNum1 = 0;
                                    int64_t memoryNum2 = 0;
                                    for (int k = 0; k < 8; k++)
                                        memoryNum1 += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        memoryNum2 += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)memory->Get(memoryNum1)) = *((int64_t*)memory->Get(memoryNum2));
                                }
                                break;

                                case 0x05: //mov m1, r1 // r1 -> m1 (000000010000000000000005)
                                {
                                    uint64_t registerNum = 0;
                                    int64_t memoryNum = 0;
                                    for (int k = 0; k < 8; k++)
                                        memoryNum += (uint64_t)i[12 + k] << (56 - 8 * k);
                                    for (int k = 0; k < 8; k++)
                                        registerNum += (int64_t)i[20 + k] << (56 - 8 * k);
                                    *((int64_t*)memory->Get(memoryNum)) = *((int64_t*)registers->Get(registerNum));
                                }
                                break;

                                default:
                                    printf("else\n");
                                    break;
                            }
                        }
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
            fflush(stdout);
            fflush(stderr);
            fprintf(stderr, "%s\n", e.what());
            exitCode = -1;
        }

        delete memory;
        delete registers;

        for (auto& Library : *Libraries)
            delete Library.second.first;

        delete Libraries;
        delete Variables;

        fclose(fptr);
    }

    clock_t endTime = clock();
    double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("\n%lf seconds\n", executionTime);

    fgetc(stdin);
    exit(exitCode);
}
