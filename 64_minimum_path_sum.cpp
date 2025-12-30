#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int m = grid.size();
        int n = grid[0].size();

        // 创建 dp 表
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];

        // 初始化第一行
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }

        // 初始化第一列
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
            }
        }

        return dp[m-1][n-1];
    }

    int minPathSumOptimized(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int m = grid.size();
        int n = grid[0].size();

        // 初始化第一行
        for (int j = 1; j < n; j++) {
            grid[0][j] += grid[0][j-1];
        }

        // 初始化第一列
        for (int i = 1; i < m; i++) {
            grid[i][0] += grid[i-1][0];
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }

        return grid[m-1][n-1];
    }
};

// 测试函数
void test_min_path_sum() {
    Solution solution;

    vector<pair<vector<vector<int>>, int>> test_cases = {
        {
            {{1,3,1},{1,5,1},{4,2,1}},
            7
        },
        {
            {{1,2,3},{4,5,6}},
            12
        },
        {
            {{1}},
            1
        },
        {
            {{1,2}},
            3
        },
        {
            {{1},{2}},
            3
        },
        {
            {{1,3,1,2},{4,5,1,3},{2,1,4,1}},
            7
        }
    };

    for (size_t i = 0; i < test_cases.size(); i++) {
        vector<vector<int>> grid_copy1 = test_cases[i].first;
        vector<vector<int>> grid_copy2 = test_cases[i].first;
        int expected = test_cases[i].second;

        int result1 = solution.minPathSum(grid_copy1);
        int result2 = solution.minPathSumOptimized(grid_copy2);

        cout << "测试用例 " << (i + 1) << ":" << endl;
        cout << "  输入: [";
        for (size_t row = 0; row < test_cases[i].first.size(); row++) {
            cout << "[";
            for (size_t col = 0; col < test_cases[i].first[row].size(); col++) {
                cout << test_cases[i].first[row][col];
                if (col < test_cases[i].first[row].size() - 1) cout << ",";
            }
            cout << "]";
            if (row < test_cases[i].first.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        cout << "  动态规划: " << result1 << " (预期: " << expected << ")";
        cout << " | 优化版本: " << result2 << " (预期: " << expected << ")";

        if (result1 == expected && result2 == expected) {
            cout << " ✓" << endl;
        } else {
            cout << " ✗" << endl;
        }
        cout << endl;
    }
}

int main() {
    test_min_path_sum();
    return 0;
}
