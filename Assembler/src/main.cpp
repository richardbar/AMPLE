#if  ( defined(_MSC_VER))
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iterator>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

#include "OPCODE HANDLERS/V2.h"


std::map<std::string, std::string> flags;


template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ClearLine(std::string line)
{
    size_t start = line.find_first_not_of(WHITESPACE);
    line = (start == std::string::npos) ? "" : line.substr(start);
    start = line.find_last_not_of(WHITESPACE);
    line = (start == std::string::npos) ? "" : line.substr(0, start + 1);

    if (line.find_first_of('#') != std::string::npos)
        line = line.substr(0, line.find_first_of('#'));
    return line;
}

bool AssembleInstruction(std::map<std::string, std::string>& line, std::vector<uint8_t*>& byteCode)
{
    switch(atoi(line["version"].c_str()))
    {
        case 2:
            if (!HandleAssembly_V2(line, byteCode, atoi(line["lineNumber"].c_str())))
                return false;
            break;
        default:
            return false;
    }

    return true;
}

bool AddLinesToCompilableLines(char* file, uint32_t fileSize, std::vector<std::map<std::string, std::string>>& compilableLines, std::vector<uint8_t*>& byteCode)
{
    std::vector<std::string> lines;
    std::string line;
    for (int i = 0; i < fileSize; i++)
    {
        if (file[i] == '\n')
        {
            lines.push_back(line);
            line = "";
        }
        line += file[i];
    }

    for (uint32_t i = 0; i < lines.size(); i++)
    {
        lines[i] = ClearLine(lines[i]);
        if (lines[i].empty())
            continue;
        std::map<std::string, std::string> tokens;
        std::vector<std::string> tk = split(lines[i], ' ');
        tokens.insert(std::pair<std::string, std::string>(std::string("lineNumber"), std::to_string(i)));
        tokens.insert(std::pair<std::string, std::string>(std::string("mnemonic"), split(tk[0], '@')[0]));
        tokens.insert(std::pair<std::string, std::string>(std::string("version"), split(tk[0], '@')[1]));
        for (int j = 1; j < tk.size(); j++)
            tokens.insert(std::pair<std::string, std::string>(std::string("arg") + std::to_string(j), tk[j]));
        tokens.insert(std::pair<std::string, std::string>(std::string("numberOfTokens"), std::to_string(tk.size() - 1)));

        compilableLines.push_back(tokens);
    }

    return true;
}

bool ReadFile(std::string& fileName, std::vector<std::map<std::string, std::string>>& compilableLines, std::vector<uint8_t*>& byteCode)
{
    uint8_t* fileContent = nullptr;
    uint32_t sizeOfFileContent;

    FILE* fptr = fopen(fileName.c_str(), "r");
    if (!fptr)
        return false;
    fseek(fptr, 0, SEEK_END);
    sizeOfFileContent = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    fileContent = (uint8_t*)malloc(sizeOfFileContent);
    fread(fileContent, 1, sizeOfFileContent, fptr);
    fclose(fptr);

    if (!AddLinesToCompilableLines((char*)fileContent, sizeOfFileContent, compilableLines, byteCode))
    {
        free(fileContent);
        return false;
    }
    for (int i = 0; i < compilableLines.size(); i++)
    {
        if (!AssembleInstruction(compilableLines[i], byteCode))
        {
            free(fileContent);
            return false;
        }
    }
    free(fileContent);
    return true;
}

int main(int argc, char** argv)
{
    std::vector<std::string> filesToAssemble;
    std::vector<std::map<std::string, std::string>> compilableLines;
    std::vector<uint8_t*> byteCode;

    for (int i = 1; i < argc; i++)
        filesToAssemble.push_back(std::string(argv[i]));

    for (int i = 0; i < filesToAssemble.size(); i++)
    {
        if (!ReadFile(filesToAssemble[i], compilableLines, byteCode))
            return 1;
        FILE* fptr = fopen(std::string(filesToAssemble[i] + std::string(".ample")).c_str(), "wb");
        if (!fptr)
            return 1;
        for (uint32_t j = 0; j < byteCode.size(); j++)
        {
            fwrite(byteCode[j], 1, 32, fptr);
            free(byteCode[j]);
        }
        fclose(fptr);
        byteCode.clear();
        compilableLines.clear();
    }

    return 0;
}