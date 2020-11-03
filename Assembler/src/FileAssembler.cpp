#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "FileAssembler.h"
#include "File.h"

bool AssembleFile(const std::string& fname) {
    std::vector<std::string> lines = std::vector<std::string>();
    std::map<std::string, int> positions = std::map<std::string, int>();
    std::vector<std::vector<uint8_t>> binary = std::vector<std::vector<uint8_t>>();

    {
        std::ifstream inputStream = std::ifstream(fname);
        std::string line = std::string();
        while (std::getline(inputStream, line)) {
            line = line.substr(
                    0,
                    (line.find_last_of('#') != std::string::npos) ? line.find_last_of('#') : line.size());
            line.erase(
                    line.begin(),
                    std::find_if(line.begin(), line.end(), [](uint8_t c) { return !std::isspace(c); })
            );
            line.erase(
                    std::find_if(line.rbegin(), line.rend(), [](uint8_t c) { return !std::isspace(c); }).base(),
                    line.end()
            );

            if (!line.empty())
                lines.push_back(line);
        }
        inputStream.close();
    }

    FindAllPositions(lines, positions);

    if (lines.empty()) {
        std::cerr << "File: \"" << fname << "\" is empty" << std::endl;
        return false;
    }

    for (auto &line : lines)
        if (!AssembleInstruction(line, positions, binary))
            return false;

    {
        char* outFname = (char*)malloc((fname.size() + 7) * sizeof(char));
        memset(outFname, 0, fname.size() + 7);
        GetFileNameWithoutExtension(fname.c_str(), fname.size(), outFname);
        strcat(outFname, ".ample");
        std::ofstream outputStream = std::ofstream(outFname, std::ios::out | std::ios::binary);
        free(outFname);
        for (auto &instructions : binary) {
            for (unsigned char instruction : instructions)
                outputStream << (uint8_t) instruction;
        }
        outputStream.close();
    }
    return true;
}

bool AssembleInstruction(const std::string& line, const std::map<std::string, int>& positions, std::vector<std::vector<uint8_t>>& binary)
{
    std::vector<std::string> tokens;
    {
        std::istringstream stream = std::istringstream(line);
        tokens = std::vector<std::string> {
            std::istream_iterator<std::string>(stream), {}
        };
    }

    if (tokens.empty())
        return false;

    std::string neumonic = tokens[0];

    uint8_t instruction[32] = { 0x00 };
    memset(instruction, 0, 32);

    if (neumonic == "opver")
    {

    }
    else if (neumonic == "halt")
    {
        instruction[0] = 0x01;
        if (tokens.size() == 2)
        {
            if (tokens[1][0] == 'r')
            {
                instruction[4] = 0x02;
                tokens[1] = tokens[1].substr(1);
            }
            else if (tokens[1][0] == 'm')
            {
                instruction[4] = 0x03;
                tokens[1] = tokens[1].substr(1);
            }
            else if ('0' <= tokens[1][0] && tokens[1][0] <= '9')
                instruction[4] = 0x01;
            ((uint64_t*)(instruction))[1] = std::stoull(tokens[1]);
        }
        else if (tokens.size() != 1)
            return false;
    }
    else if (neumonic == "jmp")
    {

    }
    else if (neumonic == "mov64")
    {
        instruction[0] = 0x03;
        if (tokens.size() != 3)
            return false;

        if (tokens[1][0] == 'r' && (('0' <= tokens[2][0] && tokens[2][0] <= '9') || tokens[2][0] == '-'))
        {
            instruction[4] = 0x00;
            tokens[1] = tokens[1].substr(1);
        }
        else if (tokens[1][0] == 'r' && tokens[2][0] =='r')
        {
            instruction[4] = 0x02;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'r' && tokens[2][0] =='m')
        {
            instruction[4] = 0x04;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'm' && (('0' <= tokens[2][0] && tokens[2][0] <= '9') || tokens[2][0] == '-'))
        {
            instruction[4] = 0x06;
            tokens[1] = tokens[1].substr(1);
        }
        else if (tokens[1][0] == 'm' && tokens[2][0] =='r')
        {
            instruction[4] = 0x08;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'm' && tokens[2][0] =='m')
        {
            instruction[4] = 0x0A;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }

        ((uint64_t*)(instruction))[1] = std::stoull(tokens[1]);
        ((int64_t*)(instruction))[2] = std::stoll(tokens[2]);
    }
    else if (neumonic == "movu64")
    {
        instruction[0] = 0x03;
        if (tokens.size() != 3)
            return false;

        if (tokens[1][0] == 'r' && ('0' <= tokens[1][0] && tokens[1][0] <= '9'))
        {
            instruction[4] = 0x0C;
            tokens[1] = tokens[1].substr(1);
        }
        else if (tokens[1][0] == 'r' && tokens[2][0] =='r')
        {
            instruction[4] = 0xE;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'r' && tokens[2][0] =='m')
        {
            instruction[4] = 0x11;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'm' && ('0' <= tokens[1][0] && tokens[1][0] <= '9'))
        {
            instruction[4] = 0x13;
            tokens[1] = tokens[1].substr(1);
        }
        else if (tokens[1][0] == 'm' && tokens[2][0] =='r')
        {
            instruction[4] = 0x15;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }
        else if (tokens[1][0] == 'm' && tokens[2][0] =='m')
        {
            instruction[4] = 0x17;
            tokens[1] = tokens[1].substr(1);
            tokens[2] = tokens[2].substr(1);
        }

        ((uint64_t*)(instruction))[1] = std::stoull(tokens[1]);
        ((uint64_t*)(instruction))[2] = std::stoull(tokens[2]);
    }
    else
    {
        std::cerr << "Neumonic: \"" << neumonic << "\" does not exist" << std::endl;
        return false;
    }
    std::vector<uint8_t> ins = std::vector<uint8_t>();
    for (int i = 0; i < 32; i++)
        ins.push_back(instruction[i]);
    binary.push_back(ins);
    return true;
}

void FindAllPositions(std::vector<std::string>& lines, std::map<std::string, int>& positions)
{
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].back() == ':')
        {
            positions.insert(std::pair<std::string, int>(lines[i].substr(0, lines[i].size() - 1), i));
            lines.erase(lines.begin() + i--);
        }
    }
}