#pragma once

#include <map>
#include <string>
#include <vector>

bool AssembleFile(const std::string& fname);
bool AssembleInstruction(const std::string& line, const std::map<std::string, int>& positions, std::vector<std::vector<uint8_t>>& binary);
void FindAllPositions(std::vector<std::string>& lines, std::map<std::string, int>& positions);