/*
78. 子集

回溯算法解法
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;

    void backtrack(const vector<int>& nums, int index, vector<int>& path) {
        // 每个节点都是一个子集
        result.push_back(path);

        // 遍历剩余元素
        for (int i = index; i < nums.size(); i++) {
            // 选择当前元素
            path.push_back(nums[i]);
            // 递归处理剩余元素
            backtrack(nums, i + 1, path);
            // 回溯：移除当前元素
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        backtrack(nums, 0, path);
        return result;
    }
};

vector<vector<int>> subsetsIterative(vector<int>& nums) {
    vector<vector<int>> result = {{}};

    for (int num : nums) {
        int current_size = result.size();
        for (int i = 0; i < current_size; i++) {
            vector<int> new_subset = result[i];
            new_subset.push_back(num);
            result.push_back(new_subset);
        }
    }

    return result;
}

vector<vector<int>> subsetsBitmap(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;

    // 遍历所有可能的子集状态
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        result.push_back(subset);
    }

    return result;
}

void test_subsets() {
    Solution solution;

    // 测试用例1
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> expected1 = {{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}};
    vector<vector<int>> result1 = solution.subsets(nums1);

    // 排序比较
    sort(result1.begin(), result1.end());
    sort(expected1.begin(), expected1.end());
    cout << "测试1: " << (result1 == expected1 ? "通过" : "失败") << endl;

    // 测试用例2
    vector<int> nums2 = {0};
    vector<vector<int>> expected2 = {{}, {0}};
    vector<vector<int>> result2 = solution.subsets(nums2);

    sort(result2.begin(), result2.end());
    sort(expected2.begin(), expected2.end());
    cout << "测试2: " << (result2 == expected2 ? "通过" : "失败") << endl;

    // 测试用例3
    vector<int> nums3 = {};
    vector<vector<int>> expected3 = {{}};
    vector<vector<int>> result3 = solution.subsets(nums3);

    sort(result3.begin(), result3.end());
    sort(expected3.begin(), expected3.end());
    cout << "测试3: " << (result3 == expected3 ? "通过" : "失败") << endl;

    // 测试用例4：验证迭代解法
    vector<int> nums4 = {1, 2};
    vector<vector<int>> result4_iter = subsetsIterative(nums4);
    vector<vector<int>> result4_backtrack = solution.subsets(nums4);

    sort(result4_iter.begin(), result4_iter.end());
    sort(result4_backtrack.begin(), result4_backtrack.end());
    cout << "测试4 (迭代 vs 回溯): " << (result4_iter == result4_backtrack ? "通过" : "失败") << endl;

    // 测试用例5：验证位图解法
    vector<int> nums5 = {1, 2, 3};
    vector<vector<int>> result5_bitmap = subsetsBitmap(nums5);
    vector<vector<int>> result5_backtrack = solution.subsets(nums5);

    sort(result5_bitmap.begin(), result5_bitmap.end());
    sort(result5_backtrack.begin(), result5_backtrack.end());
    cout << "测试5 (位图 vs 回溯): " << (result5_bitmap == result5_backtrack ? "通过" : "失败") << endl;
}

int main() {
    test_subsets();
    cout << "\n所有测试通过！" << endl;
    return 0;
}
