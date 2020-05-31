#include "Program.h"

#include "File.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"
#include "CorruptedProgramException.h"
#include "Register.h"

#include <cmath>
#include <cstdio>
#include <ctime>
#include <exception>
#include <map>

int exitCode = 0;

std::vector<Instruction> Program::GetProgram(FILE *fptr)
{
    auto returnVal = std::vector<Instruction>();

    fpos_t position;
    fgetpos(fptr, &position);
    size_t startOfProgram = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    size_t endOfProgram = ftell(fptr);
    fsetpos(fptr, &position);
    size_t sizeOfProgram = endOfProgram - startOfProgram;

    if (sizeOfProgram % (Program::matrixColumns * Program::matrixRows) != 0)
        throw CorruptedProgramException("Program is corrupted");

    int numOfInstr = int((sizeOfProgram * 1.0) / (Program::matrixColumns * Program::matrixRows));

    for (int i = 0; i < numOfInstr; i++)
    {
        Instruction d;
        for (int j = 0; j < Program::matrixColumns; j++)
        {
            for (int k = 0; k < Program::matrixRows; k++)
            {
                int data = fgetc(fptr);
                if (data == -1)
                    throw CorruptedProgramException("Program is corrupted");
                d._instruction[j][k] = (uint8_t)data;
            }
        }
        returnVal.push_back(d);
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

    if (args.size() == 1 && (args[0] == std::string("-h") || args[0] == std::string("--help")))
    {
        fprintf(stdout, "AMPLE VM\nSupports AMPLE V1\nExperimental Features\n");
        exit(0);
    }

    if (args.size() > 1 && (args[0] == std::string("-i") || args[0] == std::string("--install")))
    {
        args.erase(args.begin());
        if (!Library::InstallLibraries(args)) exit(-1);
        exit(0);
    }

    for (auto& fileName : args)
    {
        FILE* fptr = File::Open(fileName, FileMode::Read);
        if (!fptr)
        {
            fprintf(stderr, "File: \"%s\" does not exist.\n", fileName.c_str());
            exit(-1);
        }
        if ((fileName.find_last_of('.') != std::string::npos) ? fileName.substr(fileName.find_last_of('.') + 1) != std::string("ample"): true)
        {
            fclose(fptr);
            fprintf(stderr, "File: \"%s\" is not an AMPLE Executable File\n", fileName.c_str());
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

            std::vector<Instruction> program = Program::GetProgram(fptr);
        }
        catch (std::exception& e)
        {
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
    printf("\n%lf milliseconds\n", executionTime);

    exit(exitCode);
}
