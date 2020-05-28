#ifndef __AMPLE_PROGRAM_H__
#define __AMPLE_PROGRAM_H__

#include <string>
#include <vector>

typedef struct
{
    uint8_t _instruction[6][5];
} Instruction;

class Program
{
public:
    static const int matrixRows = 6;
    static const int matrixColumns = 5;
    static void Main(std::vector<std::string>& args);
private:
    static std::vector<Instruction> GetProgram(FILE* fptr);
};

#endif//__AMPLE_PROGRAM_H__