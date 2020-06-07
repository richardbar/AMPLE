#ifndef __AMPLE_PROGRAM_H__
#define __AMPLE_PROGRAM_H__

#include <string>
#include <vector>

class Program
{
public:
    static const int matrixRows = 6;
    static const int matrixColumns = 6;
    static void Main(std::vector<std::string>& args);
private:
    static std::vector<uint8_t*> GetProgram(FILE* fptr);
};

#endif//__AMPLE_PROGRAM_H__