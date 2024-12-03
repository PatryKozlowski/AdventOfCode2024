#include "helpers.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

int extractAndSumValidMultiplications(const std::string& path, const std::regex& pattern, bool isPrefixEnable)
{
    std::ifstream day3Input(path);

    if (!day3Input.is_open())
    {
        std::cout << "Can't open file: " << path << "\n";
        return 0;
    }

    std::string line;
    int multiplicationsResult = 0;
    bool isMulEnabled = true;

    while (std::getline(day3Input, line))
    {
        std::smatch match;

        while (std::regex_search(line, match, pattern))
        {
            if (isPrefixEnable)
            {
                std::string beforeMul = match.prefix().str();
                if (beforeMul.find("do()") != std::string::npos)
                {
                    isMulEnabled = true;
                }
                else if (beforeMul.find("don't()") != std::string::npos)
                {
                    isMulEnabled = false;
                }
            }

            if (isMulEnabled) {
                int first = std::stoi(match[1]);
                int second = std::stoi(match[2]);

                int multi = first * second;
                multiplicationsResult += multi;

                std::cout << " -> Matched: " << match[0]
                    << " -> Numbers: " << first << ", " << second
                    << ", Mult: " << multi << std::endl;
            }

            line = match.suffix();
        }
    }
    std::cout << "\n";
    return multiplicationsResult;
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day3.txt");
    const std::regex pattern(R"(mul\((\d+),(\d+)\))");

    int resultOfMultiplications = extractAndSumValidMultiplications(FILE_PATH, pattern, false);
    int resultOfMultiplicationsWithPrefix = extractAndSumValidMultiplications(FILE_PATH, pattern, true);

    std::cout << "Part ONE [result of multiplications]: " << resultOfMultiplications << std::endl;
    std::cout << "Part ONE [result of multiplications with prefix]: " << resultOfMultiplicationsWithPrefix << std::endl;

}