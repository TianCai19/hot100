#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        /*
         * 动态规划：时间 O(mn)，空间 O(mn)
         * dp[i][j] 表示以 (i,j) 为右下角的最大正方形边长
         * 状态转移: dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
         */
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size(), cols = matrix[0].size();
        // dp[i][j] 表示以 (i,j) 为右下角的最大正方形边长
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
        int maxSide = 0;

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (matrix[i - 1][j - 1] == '1') {
                    // 取三个方向的最小值 + 1
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;
    }
};

// ==================== 测试代码 ====================

void printMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution solution;

    // 测试用例 1
    cout << "==================================================" << endl;
    cout << "测试用例 1:" << endl;
    vector<vector<char>> matrix1 = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    cout << "矩阵:" << endl;
    printMatrix(matrix1);
    int result1 = solution.maximalSquare(matrix1);
    cout << "结果: " << result1 << endl;
    assert(result1 == 4);
    cout << "✓ 通过" << endl;

    // 测试用例 2
    cout << "\n==================================================" << endl;
    cout << "测试用例 2:" << endl;
    vector<vector<char>> matrix2 = {
        {'0', '1'},
        {'1', '0'}
    };
    cout << "矩阵:" << endl;
    printMatrix(matrix2);
    int result2 = solution.maximalSquare(matrix2);
    cout << "结果: " << result2 << endl;
    assert(result2 == 1);
    cout << "✓ 通过" << endl;

    // 测试用例 3
    cout << "\n==================================================" << endl;
    cout << "测试用例 3:" << endl;
    vector<vector<char>> matrix3 = {{'0'}};
    cout << "矩阵:" << endl;
    printMatrix(matrix3);
    int result3 = solution.maximalSquare(matrix3);
    cout << "结果: " << result3 << endl;
    assert(result3 == 0);
    cout << "✓ 通过" << endl;

    // 测试用例 4: 全1矩阵
    cout << "\n==================================================" << endl;
    cout << "测试用例 4 (全1矩阵):" << endl;
    vector<vector<char>> matrix4 = {
        {'1', '1'},
        {'1', '1'}
    };
    cout << "矩阵:" << endl;
    printMatrix(matrix4);
    int result4 = solution.maximalSquare(matrix4);
    cout << "结果: " << result4 << endl;
    assert(result4 == 4);
    cout << "✓ 通过" << endl;

    // 测试用例 5: 单行
    cout << "\n==================================================" << endl;
    cout << "测试用例 5 (单行):" << endl;
    vector<vector<char>> matrix5 = {{'1', '1', '1', '1'}};
    cout << "矩阵:" << endl;
    printMatrix(matrix5);
    int result5 = solution.maximalSquare(matrix5);
    cout << "结果: " << result5 << endl;
    assert(result5 == 1);
    cout << "✓ 通过" << endl;

    cout << "\n==================================================" << endl;
    cout << "所有测试用例通过！" << endl;

    return 0;
}
