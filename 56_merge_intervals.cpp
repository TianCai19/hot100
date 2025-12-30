#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // 按区间起始位置排序
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); i++) {
            // 如果当前区间与前一个区间重叠
            if (intervals[i][0] <= merged.back()[1]) {
                // 合并区间，更新结束位置
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // 不重叠，添加新区间
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};

// 测试函数
void test_merge() {
    Solution solution;

    vector<pair<vector<vector<int>>, vector<vector<int>>>> test_cases = {
        {
            {{1,3},{2,6},{8,10},{15,18}},
            {{1,6},{8,10},{15,18}}
        },
        {
            {{1,4},{4,5}},
            {{1,5}}
        },
        {
            {{1,4},{2,3}},
            {{1,4}}
        },
        {
            {},
            {}
        },
        {
            {{1,4},{0,4}},
            {{0,4}}
        },
        {
            {{1,4},{2,3},{5,7},{6,8}},
            {{1,4},{5,8}}
        }
    };

    for (size_t i = 0; i < test_cases.size(); i++) {
        vector<vector<int>> result = solution.merge(test_cases[i].first);
        bool passed = (result == test_cases[i].second);

        cout << "测试用例 " << (i + 1) << ": " << (passed ? "通过" : "失败") << endl;
        cout << "  输入: [";
        for (const auto& interval : test_cases[i].first) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &test_cases[i].first.back()) cout << ",";
        }
        cout << "]" << endl;

        cout << "  输出: [";
        for (const auto& interval : result) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &result.back()) cout << ",";
        }
        cout << "]" << endl;

        cout << "  预期: [";
        for (const auto& interval : test_cases[i].second) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &test_cases[i].second.back()) cout << ",";
        }
        cout << "]" << endl << endl;
    }
}

int main() {
    test_merge();
    return 0;
}
