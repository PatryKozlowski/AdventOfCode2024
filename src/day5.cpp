#include "helpers.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

std::pair<int, int> parseRule(const std::string& line)
{
    std::istringstream ss(line);
    std::string part;
    int x, y;
    if (std::getline(ss, part, '|'))
    {
        x = std::stoi(part);
    }
    if (std::getline(ss, part, '|'))
    {
        y = std::stoi(part);
    }
    return { x, y };
}

std::vector<int> parseUpdate(const std::string& line)
{
    std::istringstream ss(line);
    std::string part;
    std::vector<int> update;
    while (std::getline(ss, part, ','))
    {
        update.push_back(std::stoi(part));
    }
    return update;
}

bool followsRules(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules)
{
    std::unordered_map<int, int> indexMap;

    for (size_t i = 0; i < update.size(); ++i)
    {
        indexMap[update[i]] = i;
    }

    for (const auto& [a, b] : rules) {
        if (indexMap.find(a) != indexMap.end() && indexMap.find(b) != indexMap.end())
        {
            if (indexMap[a] >= indexMap[b])
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<int> sortCorrectly(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules)
{
    std::unordered_map<int, int> inDegree;
    std::unordered_map<int, std::vector<int>> adjList;

    for (const auto& [a, b] : rules)
    {
        if (std::find(update.begin(), update.end(), a) != update.end() &&
            std::find(update.begin(), update.end(), b) != update.end())
        {
            adjList[a].push_back(b);
            inDegree[b]++;
        }
    }

    for (int num : update)
    {
        if (inDegree.find(num) == inDegree.end())
        {
            inDegree[num] = 0;
        }
    }

    std::queue<int> q;
    for (const auto& [num, degree] : inDegree)
    {
        if (degree == 0)
        {
            q.push(num);
        }
    }

    std::vector<int> sorted;
    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        sorted.push_back(current);

        for (int neighbor : adjList[current])
        {
            if (--inDegree[neighbor] == 0)
            {
                q.push(neighbor);
            }
        }
    }

    if (sorted.size() != update.size())
    {
        std::cerr << "Error: Unable to sort updates correctly. A cycle in the dependency graph.\n";
        return {};
    }

    return sorted;
}

int calculateMiddleSum(const std::vector<std::vector<int>>& updates, const std::vector<std::pair<int, int>>& rules)
{
    int middleSum = 0;

    for (const auto& update : updates)
    {
        if (followsRules(update, rules))
        {
            size_t middleIndex = update.size() / 2;
            middleSum += update[middleIndex];
        }
    }

    return middleSum;
}

int calculateMiddleSumForInvalid(const std::vector<std::vector<int>>& updates, const std::vector<std::pair<int, int>>& rules)
{
    int middleSum = 0;

    for (const auto& update : updates)
    {
        if (followsRules(update, rules))
        {
            continue;
        }

        auto sortedUpdate = sortCorrectly(update, rules);
        if (!sortedUpdate.empty())
        {
            middleSum += sortedUpdate[sortedUpdate.size() / 2];
        }
    }

    return middleSum;
}

void readFileIntoContainers(const std::string& path, std::vector<std::pair<int, int>>& rules, std::vector<std::vector<int>>& updates)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Cant open the file: " << path << std::endl;
        return;
    }

    std::string line;
    bool parsingRules = true;

    while (std::getline(file, line))
    {
        if (line.empty()) {
            parsingRules = false;
            continue;
        }

        if (parsingRules)
        {
            rules.push_back(parseRule(line));
        }
        else
        {
            updates.push_back(parseUpdate(line));
        }
    }
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day5.txt");

    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    readFileIntoContainers(FILE_PATH, rules, updates);

    int middleSum = calculateMiddleSum(updates, rules);
    int middleSumInvalid = calculateMiddleSumForInvalid(updates, rules);

    std::cout << "Part ONE: " << middleSum << std::endl;
    std::cout << "Part TWO: " << middleSumInvalid << std::endl;
}
