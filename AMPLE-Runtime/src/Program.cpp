#include "Program.h"

#include "DllNotFoundException.h"
#include "File.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"
#include "CorruptedProgramException.h"
#include "Register.h"

#include <cmath>
#include <cstdio>
#include <exception>
#include <map>

int _exitCode = 0;

std::vector<Instruction> Program::GetProgram(FILE *fptr)
{
    auto returny = std::vector<Instruction>();

    size_t startOfProgram = ftell(fptr);
    fseek(fptr, 0, SEEK_END);
    size_t endOfProgram = ftell(fptr);
    fseek(fptr, 0, startOfProgram);
    size_t sizeOfProgram = endOfProgram - startOfProgram - 1;

    if (sizeOfProgram % (Program::matrixColumns * Program::matrixRows) != 0)
        throw CorruptedProgramException("Program is corrupted");

    int numOfInstr = floor(sizeOfProgram / (Program::matrixColumns * Program::matrixRows));

    for (int i = 0; i < numOfInstr; i++)
    {
        Instruction d;
        for (int j = 0; j < Program::matrixColumns; j++)
        {
            for (int k = 0; k < Program::matrixRows; k++)
            {
                d._instruction[j][k] = fgetc(fptr);
            }
        }
        returny.push_back(d);
    }

    return returny;
}

void Program::Main(std::vector<std::string>& args)
{
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
        Memory* memory = {0};
        Memory* registers = {0};

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
                }
                try {
                    if (!memorySet)
                        memorySize = std::stoull((*Variables)["Memory"]);
                    //printf("Setting memory to %d bytes\n", std::stoi((*Variables)["Memory"]));
                }
                catch (...) { }
            }

            memory = new Memory(memorySize);
            printf("Set memory to %ld bytes\n", memorySize);
            registers = new Register(64);

            std::vector<Instruction> program = Program::GetProgram(fptr);
        }
        catch (std::exception& e)
        {
            fprintf(stderr, "%s\n", e.what());
            _exitCode = -1;
        }

        delete memory;
        delete registers;

        for (auto& Library : *Libraries)
            delete Library.second.first;

        delete Libraries;
        delete Variables;

        fclose(fptr);
    }
    exit(_exitCode);
}
