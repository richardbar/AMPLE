#include <fstream>
#include <iostream>

#include "FileAssembler.h"
#include "File.h"


int main(int argc, const char** argv) {
    if (argc < 2)
    {
        std::cerr << "No arguments passed to AMPLE-Assembler" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (!FileExists(argv[i]))
        {
            std::cerr << "File :\"" << argv[i] << "\" does not exist" << std::endl;
            return 1;
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (!AssembleFile(argv[i]))
        {
            std::cerr << "File :\"" << argv[i] << "\" did not assemble correctly" << std::endl;
            return 1;
        }
    }
}
