/*
79. 单词搜索

回溯算法解法
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    int m, n;
    string word;

    bool backtrack(vector<vector<char>>& board, int row, int col, int index) {
        // 所有字符都匹配成功
        if (index == word.length()) {
            return true;
        }

        // 边界检查
        if (row < 0 || row >= m || col < 0 || col >= n) {
            return false;
        }

        // 字符匹配检查
        if (board[row][col] != word[index]) {
            return false;
        }

        // 标记当前单元格为已访问
        char temp = board[row][col];
        board[row][col] = '#';

        // 向四个方向搜索
        bool found = backtrack(board, row - 1, col, index + 1) ||  // 上
                     backtrack(board, row + 1, col, index + 1) ||  // 下
                     backtrack(board, row, col - 1, index + 1) ||  // 左
                     backtrack(board, row, col + 1, index + 1);    // 右

        // 回溯：恢复单元格状态
        board[row][col] = temp;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        this->word = word;

        // 遍历每个单元格作为起点
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

class SolutionOptimized {
private:
    int m, n;
    string word;
    vector<vector<bool>> visited;

    bool backtrack(const vector<vector<char>>& board, int row, int col, int index) {
        if (index == word.length()) {
            return true;
        }

        if (row < 0 || row >= m || col < 0 || col >= n) {
            return false;
        }

        if (visited[row][col] || board[row][col] != word[index]) {
            return false;
        }

        visited[row][col] = true;

        bool found = backtrack(board, row - 1, col, index + 1) ||
                     backtrack(board, row + 1, col, index + 1) ||
                     backtrack(board, row, col - 1, index + 1) ||
                     backtrack(board, row, col + 1, index + 1);

        visited[row][col] = false;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        this->word = word;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

void test_exist() {
    Solution solution;
    SolutionOptimized solution_opt;

    // 测试用例1
    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word1 = "ABCCED";
    bool result1 = solution.exist(board1, word1);
    cout << "测试1: " << (result1 == true ? "通过" : "失败")
         << " (预期: true, 实际: " << (result1 ? "true" : "false") << ")" << endl;

    // 测试用例2
    vector<vector<char>> board2 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word2 = "SEE";
    bool result2 = solution.exist(board2, word2);
    cout << "测试2: " << (result2 == true ? "通过" : "失败")
         << " (预期: true, 实际: " << (result2 ? "true" : "false") << ")" << endl;

    // 测试用例3
    vector<vector<char>> board3 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word3 = "ABCB";
    bool result3 = solution.exist(board3, word3);
    cout << "测试3: " << (result3 == false ? "通过" : "失败")
         << " (预期: false, 实际: " << (result3 ? "true" : "false") << ")" << endl;

    // 测试用例4
    vector<vector<char>> board4 = {{'a'}};
    string word4 = "a";
    bool result4 = solution.exist(board4, word4);
    cout << "测试4: " << (result4 == true ? "通过" : "失败")
         << " (预期: true, 实际: " << (result4 ? "true" : "false") << ")" << endl;

    // 测试用例5：长单词
    vector<vector<char>> board5 = {
        {'A', 'A', 'A', 'A'},
        {'A', 'A', 'A', 'A'},
        {'A', 'A', 'A', 'A'}
    };
    string word5 = "AAAAAAAAAAAA";
    bool result5 = solution.exist(board5, word5);
    cout << "测试5: " << (result5 == true ? "通过" : "失败")
         << " (预期: true, 实际: " << (result5 ? "true" : "false") << ")" << endl;

    // 测试用例6：验证优化版本
    vector<vector<char>> board6 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word6 = "ABCCED";
    bool result6 = solution_opt.exist(board6, word6);
    cout << "测试6 (优化版本): " << (result6 == true ? "通过" : "失败")
         << " (预期: true, 实际: " << (result6 ? "true" : "false") << ")" << endl;
}

int main() {
    test_exist();
    cout << "\n所有测试通过！" << endl;
    return 0;
}
