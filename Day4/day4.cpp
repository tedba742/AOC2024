#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const string TARGET{"XMAS"};
const vector<pair<int, int>> DIRECTIONS{
    {0, 1},    // E
    {0, -1},   // W
    {1, 0},    // S
    {-1, 0},   // N
    {1, 1},    // SE
    {1, -1},   // SW
    {-1, 1},   // NE
    {-1, -1}   // NW
};

bool matchWord(const vector<string>& grid, int x, int y, int dx, int dy) {
    const int rows{static_cast<int>(grid.size())};
    const int cols{static_cast<int>(grid[0].size())};
    const int wordLength{static_cast<int>(TARGET.size())};

    for (int i{0}; i < wordLength; ++i) {
        int nx{x + dx * i};
        int ny{y + dy * i};

        if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != TARGET[i]) {
            return false;
        }
    }
    return true;
}

int countOccurrencesOfXMAS(const vector<string>& grid) {
    const int rows{static_cast<int>(grid.size())};
    const int cols{static_cast<int>(grid[0].size())};
    int count{0};

    for (int x{0}; x < rows; ++x) {
        for (int y{0}; y < cols; ++y) {
            for (const auto& [dx, dy] : DIRECTIONS) {
                if (matchWord(grid, x, y, dx, dy)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

int main() {
    ifstream file{"input.txt"};
    vector<string> grid{};
    string line{};

    while (getline(file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }

    const int result{countOccurrencesOfXMAS(grid)};
    cout << "Total 'XMAS' found in all directions: " << result << '\n';

    return 0;
}
