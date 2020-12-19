#include <string.h>

#include "AMPLE-Assembler.hpp"
#include "OPCODE HANDLERS/V2.h"

static bool CheckIfValidRegister(std::string& arguments)
{
    if (arguments.length() < 2)
        return false;
    if (arguments[0] != 'r')
        return false;
    for (int i = 1; i < arguments.length(); i++)
    {
        if (((arguments[i] - '0') < 0) || (9 < (arguments[i] - '0')))
            return false;
    }
    int registerNumber = atoi(arguments.c_str());
    return registerNumber < 64;
}
static bool CheckIfValidMemory(std::string& arguments)
{
    if (arguments.length() < 2)
        return false;
    if (arguments[0] != 'm')
        return false;
    for (int i = 1; i < arguments.length(); i++)
    {
        if (((arguments[i] - '0') < 0) || (9 < (arguments[i] - '0')))
            return false;
    }
    return true;
}
static bool CheckIfValidNumber(std::string& arguments)
{
    if (!arguments.length())
        return false;
    for (int i = 0; i < arguments.length(); i++)
    {
        if (((arguments[i] - '0') < 0) || (9 < (arguments[i] - '0')))
            return false;
    }
    return true;
}

bool AssembleMOV(LINE_ARGS)
{
    int numberOfArguments = atoi(tokens["numberOfTokens"].c_str());

    if (numberOfArguments != 2)
    {
        if (MapHasKey(tokens, std::string("unprocessedLine")))
            fprintf(stderr, "%s\n", tokens["unprocessedLine"].c_str());
        fprintf(stderr, "Line can not have %s arguments than 2", (numberOfArguments < 2) ? "fewer" : "more");
        return false;
    }

    if (!CheckIfValidRegister(tokens["arg1"]) && !CheckIfValidMemory(tokens["arg1"]))
    {
        if (MapHasKey(tokens, std::string("unprocessedLine")))
            fprintf(stderr, "%s\n", tokens["unprocessedLine"].c_str());
        fprintf(stderr, "\"%s\" is not a valid register or memory position", tokens["arg1"].c_str());
        return false;
    }
    if (!CheckIfValidRegister(tokens["arg2"]) && !CheckIfValidMemory(tokens["arg2"]) && !CheckIfValidNumber(tokens["arg2"]))
    {
        if (MapHasKey(tokens, std::string("unprocessedLine")))
            fprintf(stderr, "%s\n", tokens["unprocessedLine"].c_str());
        fprintf(stderr, "\"%s\" is not a valid register, memory or number position", tokens["arg2"].c_str());
        return false;
    }

    uint8_t* newBytes = new uint8_t[32];
    memset(newBytes, 0, 32);
    newBytes[0] = 0x03;
    if (CheckIfValidRegister(tokens["arg1"]))
        *((uint32_t*)&newBytes[4]) |= 0b1 << 4;
    else
        *((uint32_t*)&newBytes[4]) |= 0b1 << 5;

    if (CheckIfValidRegister(tokens["arg2"]))
        *((uint32_t*)&newBytes[4]) |= 0b1 << 2;
    else if (CheckIfValidMemory(tokens["arg1"]))
        *((uint32_t*)&newBytes[4]) |= 0b1 << 3;
    else
        *((uint32_t*)&newBytes[4]) |= 0b1;
    newBytes[5] = 0x01;

    *((int64_t*)&newBytes[8]) = atoll(tokens["arg1"].substr(1).c_str());
    *((int64_t*)&newBytes[16]) = atoll(tokens["arg2"].substr((!CheckIfValidNumber(tokens["arg2"])) ? 1 : 0).c_str());

    bytecode.push_back(newBytes);
    return true;
}