/**
 * 200. 岛屿数量
 * https://leetcode.com/problems/number-of-islands/
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Solution {
private:
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int r, int c) {
        // 边界检查
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '0') {
            return;
        }

        // 标记当前陆地（视为已访问）
        grid[r][c] = '0';

        // 递归访问四个方向
        dfs(grid, r - 1, c);  // 上
        dfs(grid, r + 1, c);  // 下
        dfs(grid, r, c - 1);  // 左
        dfs(grid, r, c + 1);  // 右
    }

public:
    /** 解法一：DFS（深度优先搜索） */
    int numIslands_dfs(vector<vector<char>>& grid) {
        /**
         * DFS 算法 - 深度优先搜索
         * 时间复杂度: O(M × N)，M = 行数，N = 列数
         * 空间复杂度: O(M × N)，最坏情况为全为陆地时的递归栈深度
         */
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        rows = grid.size();
        cols = grid[0].size();
        int island_count = 0;

        // 遍历每个单元格
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    island_count++;
                    // 从当前位置开始 DFS
                    dfs(grid, r, c);
                }
            }
        }

        return island_count;
    }

    /** 解法二：BFS（广度优先搜索） */
    int numIslands_bfs(vector<vector<char>>& grid) {
        /**
         * BFS 算法 - 广度优先搜索
         * 时间复杂度: O(M × N)，M = 行数，N = 列数
         * 空间复杂度: O(min(M, N))，队列中最多存储一个岛屿的所有陆地
         */
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();
        int island_count = 0;

        // 四个方向：上、下、左、右
        vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        // 遍历每个单元格
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    island_count++;
                    // 从当前位置开始 BFS
                    queue<pair<int, int>> q;
                    q.push({r, c});
                    grid[r][c] = '0';  // 标记为已访问

                    // BFS 遍历
                    while (!q.empty()) {
                        auto [cr, cc] = q.front();
                        q.pop();

                        // 检查四个方向
                        for (const auto& dir : directions) {
                            int nr = cr + dir.first;
                            int nc = cc + dir.second;

                            // 边界检查和陆地检查
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                                grid[nr][nc] == '1') {
                                q.push({nr, nc});
                                grid[nr][nc] = '0';  // 标记为已访问
                            }
                        }
                    }
                }
            }
        }

        return island_count;
    }
};

vector<vector<char>> createGrid(const vector<vector<string>>& grid_str) {
    vector<vector<char>> grid;
    for (const auto& row_str : grid_str) {
        vector<char> row;
        for (const auto& s : row_str) {
            row.push_back(s[0]);  // 取字符串的第一个字符
        }
        grid.push_back(row);
    }
    return grid;
}

vector<vector<char>> copyGrid(const vector<vector<char>>& grid) {
    return grid;
}

void testSolution(const string& name, int (Solution::*method)(vector<vector<char>>&)) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "测试方法: " << name << "\n";
    cout << string(60, '=') << "\n";

    struct TestCase {
        vector<vector<string>> grid_str;
        int expected;
        string description;
    };

    vector<TestCase> test_cases = {
        {
            {{"1", "1", "1", "1", "0"},
             {"1", "1", "0", "1", "0"},
             {"1", "1", "0", "0", "0"},
             {"0", "0", "0", "0", "0"}},
            1,
            "示例1：单个岛屿"
        },
        {
            {{"1", "1", "0", "0", "0"},
             {"1", "1", "0", "0", "0"},
             {"0", "0", "1", "0", "0"},
             {"0", "0", "0", "1", "1"}},
            3,
            "示例2：三个岛屿"
        },
        {
            {},
            0,
            "空网格"
        },
        {
            {{"0"}},
            0,
            "单个水格"
        },
        {
            {{"1"}},
            1,
            "单个陆地"
        },
        {
            {{"1", "0"},
             {"0", "1"}},
            2,
            "对角线岛屿"
        },
        {
            {{"1", "1"},
             {"1", "1"}},
            1,
            "2x2 完整岛屿"
        },
        {
            {{"1", "1", "1"},
             {"1", "0", "1"},
             {"1", "1", "1"}},
            1,
            "环形岛屿"
        },
        {
            {{"1", "1", "0", "1", "1"},
             {"0", "1", "0", "0", "0"},
             {"0", "0", "0", "1", "1"},
             {"1", "0", "0", "0", "0"}},
            4,
            "复杂形状岛屿"
        },
        {
            {{"1", "0", "1", "0", "1"},
             {"0", "1", "0", "1", "0"},
             {"1", "0", "1", "0", "1"},
             {"0", "1", "0", "1", "0"}},
            10,
            "棋盘格岛屿"
        }
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < test_cases.size(); i++) {
        const auto& test = test_cases[i];
        try {
            vector<vector<char>> grid = createGrid(test.grid_str);
            Solution solution;
            int result = (solution.*method)(grid);

            if (result == test.expected) {
                cout << "✓ 测试 " << (i + 1) << " 通过: " << test.description << "\n";
                cout << "  网格: [" << test.grid_str.size() << "×"
                     << (test.grid_str.empty() ? 0 : test.grid_str[0].size()) << "]\n";
                cout << "  岛屿数: " << result << "\n";
                passed++;
            } else {
                cout << "✗ 测试 " << (i + 1) << " 失败: " << test.description << "\n";
                cout << "  网格: [" << test.grid_str.size() << "×"
                     << (test.grid_str.empty() ? 0 : test.grid_str[0].size()) << "]\n";
                cout << "  期望: " << test.expected << ", 实际: " << result << "\n";
                failed++;
            }
        } catch (const exception& e) {
            cout << "✗ 测试 " << (i + 1) << " 出现异常: " << test.description << "\n";
            cout << "  异常: " << e.what() << "\n";
            failed++;
        }
    }

    cout << string(60, '-') << "\n";
    cout << "测试结果: " << passed << " 通过, " << failed << " 失败\n";
    cout << string(60, '-') << "\n";

    if (failed == 0) {
        cout << "✓ " << name << " 所有测试通过!\n";
    }
}

int main() {
    cout << "=" << string(60, '=') << "\n";
    cout << "测试岛屿数量\n";
    cout << string(60, '=') << "\n";

    // 测试 DFS
    testSolution("DFS", &Solution::numIslands_dfs);

    // 测试 BFS
    testSolution("BFS", &Solution::numIslands_bfs);

    cout << "\n" << string(60, '=') << "\n";
    cout << "所有测试完成!\n";
    cout << string(60, '=') << "\n";

    return 0;
}
