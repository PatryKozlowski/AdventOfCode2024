#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "helpers.hpp"

const std::vector<std::pair<int, int>> directions = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0},
    {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
};

void readFileIntoContainers(const std::string& path, std::vector<std::string>& grid)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        std::cerr << "Can't open file: " << path << "\n";
        return;
    }

    std::string line;
    while (std::getline(input, line))
    {
        grid.push_back(line);
    }
}

bool isWordFound(const std::vector<std::string>& grid, int x, int y, int dx, int dy, const std::string& word)
{
    int n = grid.size();
    int m = grid[0].size();
    int wordLen = word.size();

    for (int i = 0; i < wordLen; ++i)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != word[i])
        {
            return false;
        }
    }
    return true;
}

bool checkXMas(int i, int j, const std::vector<std::string>& grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if (i <= 0 || i >= n - 1 || j <= 0 || j >= m - 1)
    {
        return false;
    }
    if (grid[i][j] != 'A')
    {
        return false;
    }

    std::string diag_1 = { grid[i - 1][j - 1], grid[i + 1][j + 1] };
    std::string diag_2 = { grid[i - 1][j + 1], grid[i + 1][j - 1] };

    return (diag_1 == "MS" || diag_1 == "SM") && (diag_2 == "MS" || diag_2 == "SM");
}


int xmasCountOccurrences(const std::vector<std::string>& grid)
{
    int n = grid.size();
    int m = grid[0].size();
    int ans = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        for (int j = 1; j < m - 1; ++j)
        {
            ans += checkXMas(i, j, grid);
        }
    }

    return ans;
}

int countOccurrences(const std::vector<std::string>& grid, const std::string& word)
{
    int n = grid.size();
    int m = grid[0].size();
    int count = 0;

    for (int x = 0; x < n; ++x)
    {
        for (int y = 0; y < m; ++y)
        {
            for (const auto& dir : directions)
            {
                if (isWordFound(grid, x, y, dir.first, dir.second, word))
                {
                    ++count;
                }
            }
        }
    }
    return count;
}

int main()
{
    const std::string FILE_PATH = getInputFilePathForDay("day4.txt");
    const std::string WORD = "XMAS";
    std::vector<std::string> grid;

    readFileIntoContainers(FILE_PATH, grid);

    int resultXMAS = countOccurrences(grid, WORD);
    int resultX_MAS = xmasCountOccurrences(grid);

    std::cout << "Part ONE [XMAS appear]: " << resultXMAS << std::endl;
    std::cout << "Part TWO [X-MAS appear]: " << resultX_MAS << std::endl;
}
