#include "Metadata.h"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

/**
 *
 * @param fptr File Pointer to read from
 * @param libs A Map that pairs an int assigned to an Library and a
 * Map that pairs each Library's functions to a function Pointer
 */
void LoadMetaData(FILE*& fptr, std::map<int, std::pair<Library*, std::map<int, void*>>>& libs)
{
    std::string line;
    std::map<std::string, int> libraryNames = std::map<std::string, int>();
    while (true)
    {
        char c;
        while ((c = fgetc(fptr)) != -1)
        {
            if (c == '\n')
                break;
            line += c;
        }
        if (c == -1) break;

        if (line == std::string("--End of Metadata--"))
            break;

        auto lineSpaces = split(line, std::string(" "));
        if (lineSpaces.size() < 4) { }
            //error

        if (lineSpaces[0] == std::string("using") && lineSpaces[1] == std::string("as"))
        {
            int pos = std::stoi(lineSpaces[2]);
            std::pair<Library*, std::map<int, void*>> val = std::pair<Library*, std::map<int, void*>>();
            std::string libf = std::string(lineSpaces[3]);
            val.first = new Library(libf);
            val.second = std::map<int, void*>();
            libs[pos] = val;
            std::string libName = lineSpaces[3];
            libraryNames[libName] = pos;
        }
        else if (lineSpaces[0] == std::string("implement") && lineSpaces[1] == std::string("as"))
        {
            auto funcCore = split(lineSpaces[3], std::string("::"));
            auto fname = funcCore[1];
            int lpos = libraryNames[funcCore[0]];
            int fpos = std::stoi(lineSpaces[2]);
            libs[lpos].second[fpos] = libs[lpos].first->GetFunction(fname);
        }
        line = "";
    }
}