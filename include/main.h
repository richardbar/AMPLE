#ifndef __AMPLE_MAIN_H__
#define __AMPLE_MAIN_H__

#include "AMPLE.h"

#include <list>
#include <string>

#define HANDLED_MAIN(CLASS)\
int main(int argc, char** argv)\
{\
    auto args = std::vector<std::string>();\
    for (int i = 1; i < argc; i++)\
    args.emplace_back(std::string(argv[i]));\
    CLASS::Main(args);\
}

#endif//__AMPLE_MAIN_H__
