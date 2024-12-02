#include "helpers.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream> 

bool isSorted(const std::vector<int>& vector)
{
    return (std::ranges::is_sorted(vector) || std::ranges::is_sorted(vector, std::ranges::greater{}));
}

bool isValidRange(const std::vector<int>& vector)
{
    return std::adjacent_find(vector.begin(), vector.end(), [](auto a, auto b) {
        return std::abs(b - a) < 1 || std::abs(b - a) > 3;
        }) == vector.end();
}

bool isSafeReport(const std::vector<int>& report)
{
    return isSorted(report) && isValidRange(report);
}

bool canBeMadeSafeByRemovingOneLevel(const std::vector<int>& report)
{
    for (size_t i = 0; i < report.size(); i++)
    {
        std::vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i);

        if (isSafeReport(modifiedReport))
        {
            return true;
        }
    }

    return false;
}

int countSafeReports(const std::string& path, bool isDampener)
{
    std::fstream day2Input(path);

    if (!day2Input.is_open())
    {
        std::cout << "Can't open file: " << path << "\n";
        return 0;
    }

    std::string line;
    int countSafeReports = 0;

    while (std::getline(day2Input, line))
    {
        std::istringstream ss(line);
        std::vector<int> numbers;
        int number;

        while (ss >> number)
        {
            numbers.push_back(number);
        }

        if (isSafeReport(numbers))
        {
            countSafeReports++;
        }
        else if (isDampener && canBeMadeSafeByRemovingOneLevel(numbers))
        {
            countSafeReports++;
        }
    }

    return countSafeReports;
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day2.txt");

    int totalSafeReports = countSafeReports(FILE_PATH, false);
    int totalSafeReportsWithDampener = countSafeReports(FILE_PATH, true);

    std::cout << "Part ONE [total safe reports]: " << totalSafeReports << std::endl;
    std::cout << "Part ONE [total safe reports with remove Dampener Problem]: " << totalSafeReportsWithDampener << std::endl;
}