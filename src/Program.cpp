#include "Program.h"

#include "DllNotFoundException.h"
#include "File.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"

#include <cstdio>
#include <exception>
#include <map>

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

        try {
            auto Libraries = new std::map<int, std::pair<Library*, std::map<int, void*>>>();
            auto Variables = new std::map<std::string, std::string>();
            LoadMetaData(fptr, *Libraries, *Variables);

            int memorySize = 1024;
            if (Variables->find("Memory") != Variables->end())
            {
                try {
                    memorySize = std::stoi((*Variables)["Memory"]);
                    printf("Setting memory to %d\n", std::stoi((*Variables)["Memory"]));
                }
                catch (...) { }
            }
            Memory::InitializeMemory(sizeof(int64_t), memorySize);



            Memory::FreeMemory();
            delete Libraries;
            delete Variables;
        }
        catch (std::exception& e)
        {
            printf("%s\n", e.what());
        }


        fclose(fptr);
    }
    exit(0);
}