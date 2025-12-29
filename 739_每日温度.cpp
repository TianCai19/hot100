#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        /*
         * 单调栈法：时间 O(n)，空间 O(n)
         * 维护单调递减栈，存储温度的索引
         * 当遇到更高温度时，弹出栈顶并计算天数差
         */
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> st;  // 单调递减栈，存储索引

        for (int i = 0; i < n; i++) {
            // 当栈不为空且当前温度 > 栈顶温度
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevIndex = st.top();
                st.pop();
                answer[prevIndex] = i - prevIndex;
            }
            st.push(i);
        }

        return answer;
    }
};

// ==================== 测试代码 ====================

void printResult(const vector<int>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1
    cout << "==================================================" << endl;
    cout << "测试用例 1:" << endl;
    vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    cout << "温度: [73, 74, 75, 71, 69, 72, 76, 73]" << endl;
    vector<int> result1 = solution.dailyTemperatures(temps1);
    cout << "结果: "; printResult(result1);
    assert(result1.size() == 8 && result1[0] == 1 && result1[2] == 4);
    cout << "✓ 通过" << endl;

    // 测试用例 2
    cout << "\n==================================================" << endl;
    cout << "测试用例 2:" << endl;
    vector<int> temps2 = {30, 40, 50, 60};
    cout << "温度: [30, 40, 50, 60]" << endl;
    vector<int> result2 = solution.dailyTemperatures(temps2);
    cout << "结果: "; printResult(result2);
    assert(result2.size() == 4 && result2[0] == 1 && result2[3] == 0);
    cout << "✓ 通过" << endl;

    // 测试用例 3
    cout << "\n==================================================" << endl;
    cout << "测试用例 3:" << endl;
    vector<int> temps3 = {30, 60, 90};
    cout << "温度: [30, 60, 90]" << endl;
    vector<int> result3 = solution.dailyTemperatures(temps3);
    cout << "结果: "; printResult(result3);
    assert(result3.size() == 3 && result3[0] == 1 && result3[2] == 0);
    cout << "✓ 通过" << endl;

    // 测试用例 4: 递减温度
    cout << "\n==================================================" << endl;
    cout << "测试用例 4 (递减温度):" << endl;
    vector<int> temps4 = {90, 80, 70, 60};
    cout << "温度: [90, 80, 70, 60]" << endl;
    vector<int> result4 = solution.dailyTemperatures(temps4);
    cout << "结果: "; printResult(result4);
    assert(result4.size() == 4 && result4[0] == 0 && result4[3] == 0);
    cout << "✓ 通过" << endl;

    // 测试用例 5: 相同温度
    cout << "\n==================================================" << endl;
    cout << "测试用例 5 (相同温度):" << endl;
    vector<int> temps5 = {50, 50, 50};
    cout << "温度: [50, 50, 50]" << endl;
    vector<int> result5 = solution.dailyTemperatures(temps5);
    cout << "结果: "; printResult(result5);
    assert(result5.size() == 3 && result5[0] == 0 && result5[2] == 0);
    cout << "✓ 通过" << endl;

    cout << "\n==================================================" << endl;
    cout << "所有测试用例通过！" << endl;

    return 0;
}
