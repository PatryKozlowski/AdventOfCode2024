#include <helpers.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>

int calculatePatrolPath(const std::vector<std::string>& grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int i = 0, j = 0, dir = 0;
    bool found = false;
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < m; ++col)
        {
            if (grid[row][col] == '^')
            {
                i = row;
                j = col;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    const int dd[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    std::set<std::pair<int, int>> seen;

    while (true)
    {
        seen.insert({ i, j });

        int next_i = i + dd[dir][0];
        int next_j = j + dd[dir][1];

        if (next_i < 0 || next_j < 0 || next_i >= n || next_j >= m)
        {
            break;
        }

        if (grid[next_i][next_j] == '#')
        {
            dir = (dir + 1) % 4;
        }
        else
        {
            i = next_i;
            j = next_j;
        }
    }

    return seen.size();
}

bool willLoop(std::vector<std::string>& grid, int oi, int oj, int ii, int jj)
{
    int n = grid.size();
    int m = grid[0].size();

    if (grid[oi][oj] == '#')
    {
        return false;
    }

    grid[oi][oj] = '#';

    int i = ii, j = jj, dir = 0;
    std::set<std::tuple<int, int, int>> seen;

    const int dd[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    while (true)
    {
        if (seen.find({ i, j, dir }) != seen.end())
        {
            grid[oi][oj] = '.';
            return true;
        }

        seen.insert({ i, j, dir });

        int next_i = i + dd[dir][0];
        int next_j = j + dd[dir][1];

        if (next_i < 0 || next_j < 0 || next_i >= n || next_j >= m)
        {
            grid[oi][oj] = '.';
            return false;
        }

        if (grid[next_i][next_j] == '#')
        {
            dir = (dir + 1) % 4;
        }
        else
        {
            i = next_i;
            j = next_j;
        }
    }
}

std::pair<int, int> findGuardStart(const std::vector<std::string>& grid)
{
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (grid[i][j] == '^')
            {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}

int findLoopPositions(std::vector<std::string>& grid, int start_i, int start_j)
{
    int n = grid.size();
    int m = grid[0].size();

    std::set<std::pair<int, int>> visited;
    int dir = 0;
    int i = start_i, j = start_j;

    const int dd[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    while (true)
    {
        visited.insert({ i, j });

        int next_i = i + dd[dir][0];
        int next_j = j + dd[dir][1];

        if (next_i < 0 || next_j < 0 || next_i >= n || next_j >= m) break;

        if (grid[next_i][next_j] == '#')
        {
            dir = (dir + 1) % 4;
        }
        else
        {
            i = next_i;
            j = next_j;
        }
    }

    int result = 0;
    for (auto& [oi, oj] : visited)
    {
        if (willLoop(grid, oi, oj, start_i, start_j))
        {
            ++result;
        }
    }

    return result;
}

void readFileIntoContainers(const std::string& path, std::vector<std::string>& map)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Cant open the file: " << path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        map.push_back(line);
    }
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day6.txt");
    std::vector<std::string> map;

    readFileIntoContainers(FILE_PATH, map);

    int distancePosition = calculatePatrolPath(map);
    std::cout << "PART ONE: " << distancePosition << std::endl;

    auto [start_i, start_j] = findGuardStart(map);
    int loopPositions = findLoopPositions(map, start_i, start_j);
    std::cout << "PART TWO: " << loopPositions << std::endl;
}