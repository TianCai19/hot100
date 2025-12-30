#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // 创建 dp 表
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 初始化第一行
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // 初始化第一列
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }

    int uniquePathsOptimized(int m, int n) {
        // 使用一维数组优化空间
        vector<int> dp(n, 1);  // 初始化为 1，第一行的所有位置都只能从左边到达

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j-1];
            }
        }

        return dp[n-1];
    }

    // 组合数学解法
    long long uniquePathsCombination(int m, int n) {
        // 计算 C(a, b) = a! / (b! * (a-b)!)
        // 使用 long long 防止溢出
        long long a = m + n - 2;
        long long b = min(m - 1, n - 1);

        long long result = 1;
        for (long long i = 1; i <= b; i++) {
            result = result * (a - i + 1) / i;
        }

        return result;
    }
};

// 测试函数
void test_unique_paths() {
    Solution solution;

    vector<tuple<int, int, int>> test_cases = {
        {3, 7, 28},
        {2, 3, 3},
        {3, 3, 6},
        {1, 1, 1},
        {1, 5, 1},
        {5, 1, 1}
    };

    for (const auto& test : test_cases) {
        int m, n, expected;
        tie(m, n, expected) = test;

        int result = solution.uniquePaths(m, n);
        int result_opt = solution.uniquePathsOptimized(m, n);
        long long result_comb = solution.uniquePathsCombination(m, n);

        cout << "m=" << m << ", n=" << n << ":";
        cout << " 动态规划: " << result << " (预期: " << expected << ")";
        cout << " | 优化版本: " << result_opt << " (预期: " << expected << ")";
        cout << " | 组合数学: " << result_comb << " (预期: " << expected << ")";

        if (result == expected && result_opt == expected && result_comb == expected) {
            cout << " ✓" << endl;
        } else {
            cout << " ✗" << endl;
        }
    }
}

int main() {
    test_unique_paths();
    return 0;
}
