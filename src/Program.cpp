#include "Program.h"
#include "DllNotFoundException.h"
#include "IndexOutOfRangeException.h"
#include "Library.h"
#include "Memory.h"
#include "Metadata.h"
#include "MissingMethodException.h"

#include <cstdio>

bool FileExists(std::string& file)
{
    FILE* fptr = fopen(file.c_str(), "r");
    if (fptr)
    {
        fclose(fptr);
        return true;
    }
    return false;
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
        if (!FileExists(fileName))
        {
            fprintf(stderr, "File: \"%s\" does not exist.\n", fileName.c_str());
            exit(-1);
        }
        if ((fileName.find_last_of('.') != std::string::npos) ? fileName.substr(fileName.find_last_of('.') + 1) != std::string("ample"): true)
        {
            fprintf(stderr, "File: \"%s\" is not an AMPLE Executable File\n", fileName.c_str());
            exit(-1);
        }

        FILE* fptr = fopen(fileName.c_str(), "r");

        try {
            auto Libraries = std::map<int, std::pair<Library*, std::map<int, void*>>>();
            LoadMetaData(fptr, Libraries);

            Memory::InitializeMemory(sizeof(int64_t), 1024);

            Memory::FreeMemory();
        }
        catch (MissingMethodException& e)
        {
            printf("%s\n", e.what());
        }
        catch (DllNotFoundException& e)
        {
            printf("%s\n", e.what());
        }
        catch (IndexOutOfRangeException& e)
        {
            printf("%s\n", e.what());
        }


        fclose(fptr);
    }
    exit(0);
}