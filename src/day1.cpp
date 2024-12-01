#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include "helpers.hpp"

template <typename T, typename N>
void readFileIntoContainers(const std::string& path, T& leftSide, N& rightSide)
{
    std::fstream day1Input(path);

    if (!day1Input.is_open())
    {
        std::cerr << "Can't open file: " << path << "\n";
    }

    std::string line;

    while (std::getline(day1Input, line))
    {
        std::istringstream lineStream(line);

        int leftValue = -1;
        int rightValue = -1;

        if (lineStream >> leftValue >> rightValue)
        {
            leftSide.push_back(leftValue);
            rightSide.push_back(rightValue);
        }
    }
}

template <typename T, typename N>
int calculateTotalDistance(T& leftInput, N& rightInput)
{
    std::ranges::sort(leftInput);
    std::ranges::sort(rightInput);

    int totalDistance = 0;

    for (size_t i = 0; i < leftInput.size(); ++i)
    {
        totalDistance += std::abs(leftInput[i] - rightInput[i]);
    }
    return totalDistance;
}

template <typename T, typename N>
int calculateSimilarityScore(const T& left, const N& right) {
    std::unordered_map<int, int> rightCount;

    for (int num : right)
    {
        rightCount[num]++;
    }

    int similarityScore = 0;
    for (int num : left)
    {
        similarityScore += num * rightCount[num];
    }

    return similarityScore;
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day1.txt");

    std::vector<int> left;
    std::vector<int> right;

    readFileIntoContainers(FILE_PATH, left, right);

    if (left.empty() || right.empty())
    {
        std::cout << "Container of data is empty !";
        return 0;
    }

    std::cout << "Part ONE: " << calculateTotalDistance(left, right) << std::endl;

    std::cout << "Part TWO: " << calculateSimilarityScore(left, right) << std::endl;
}