#include "AMPLE-Assembler.hpp"
#include "OPCODE HANDLERS/V2.h"

std::map<std::string, bool(*)(LINE_ARGS)> mnemonics = {
        { std::string("mov"), AssembleMOV },
        { std::string("MOV"), AssembleMOV },
        { std::string("add"), AssembleADD },
        { std::string("ADD"), AssembleADD },
        { std::string("sub"), AssembleSUB },
        { std::string("SUB"), AssembleSUB },
        { std::string("mult"), AssembleMULT },
        { std::string("MULT"), AssembleMULT },
        { std::string("div"), AssembleDIV },
        { std::string("DIV"), AssembleDIV },
        { std::string("mod"), AssembleMOD },
        { std::string("MOD"), AssembleMOD },
        { std::string("lshift"), AssembleLSHIFT },
        { std::string("LSHIFT"), AssembleLSHIFT },
        { std::string("rshift"), AssembleDIV },
        { std::string("RSHIFT"), AssembleRSHIFT }
};

bool HandleAssembly_V2(LINE_ARGS)
{
    if  (!MapHasKey(tokens, std::string("mnemonic")) || !MapHasKey(tokens, std::string("numberOfTokens")))
        return false;

    if (!MapHasKey(mnemonics, tokens["mnemonic"]))
    {
        fprintf(stderr, "Mnemonic \"%s\" does not exist\n", tokens["mnemonic"].c_str());
        return false;
    }

    return mnemonics[tokens["mnemonic"]](tokens, bytecode, lineNumber);
}