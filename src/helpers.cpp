#include "helpers.hpp"

std::string getInputFilePathForDay(const std::string& day)
{
    std::filesystem::path projectRoot = "/Users/patrykkozlowski/Desktop/Projekty/AdventOfCode2024";
    std::string relativePath = "input/" + day;
    std::string filePath = (projectRoot / relativePath).string();
    return filePath;
}