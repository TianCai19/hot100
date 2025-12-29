/**
 * 215. 数组中的第 K 个最大元素
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <functional>
using namespace std;

class Solution {
private:
    int partition(vector<int>& nums, int left, int right, int pivot_index) {
        int pivot = nums[pivot_index];
        // 1. 将基准元素移到末尾
        swap(nums[pivot_index], nums[right]);
        int store_index = left;

        // 2. 将所有比基准大的元素移到左边
        for (int i = left; i < right; i++) {
            if (nums[i] < pivot) {
                swap(nums[store_index], nums[i]);
                store_index++;
            }
        }

        // 3. 将基准元素移回正确位置
        swap(nums[right], nums[store_index]);
        return store_index;
    }

    int quickselect(vector<int>& nums, int left, int right, int target) {
        if (left == right) {
            return nums[left];
        }

        // 随机选择基准元素
        int pivot_index = left + rand() % (right - left + 1);
        pivot_index = partition(nums, left, right, pivot_index);

        if (pivot_index == target) {
            return nums[pivot_index];
        } else if (pivot_index < target) {
            return quickselect(nums, pivot_index + 1, right, target);
        } else {
            return quickselect(nums, left, pivot_index - 1, target);
        }
    }

public:
    /** 解法一：排序法 */
    int findKthLargest_sort(vector<int>& nums, int k) {
        /**
         * 直接排序法
         * 时间复杂度: O(n log n)
         * 空间复杂度: O(1)
         */
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[k - 1];
    }

    /** 解法二：最小堆（推荐） */
    int findKthLargest_heap(vector<int>& nums, int k) {
        /**
         * 最小堆维护前 k 个最大元素
         * 时间复杂度: O(n log k)
         * 空间复杂度: O(k)
         */
        priority_queue<int, vector<int>, greater<int>> min_heap;

        for (int num : nums) {
            min_heap.push(num);
            if ((int)min_heap.size() > k) {
                min_heap.pop();
            }
        }

        return min_heap.top();
    }

    /** 解法三：快速选择算法 */
    int findKthLargest_quickselect(vector<int>& nums, int k) {
        /**
         * 基于快速排序的选择算法
         * 平均时间复杂度: O(n)
         * 最坏时间复杂度: O(n²)
         * 空间复杂度: O(1)
         */
        int n = nums.size();
        int target = n - k;
        srand(time(0));  // 设置随机种子
        return quickselect(nums, 0, n - 1, target);
    }
};

struct TestCase {
    vector<int> nums;
    int k;
    int expected;
};

void test_solution() {
    Solution solution;

    vector<TestCase> test_cases = {
        {{3, 2, 1, 5, 6, 4}, 2, 5},
        {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4, 4},
        {{1}, 1, 1},
        {{2, 1}, 1, 2},
        {{2, 1}, 2, 1},
        {{3, 3, 3, 3, 3, 3}, 1, 3},
        {{-1, -2, -3}, 1, -1},
        {{-1, -2, -3}, 3, -3},
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 8},
        {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5, 6}
    };

    vector<pair<string, function<int(vector<int>&, int)>>> methods = {
        {"排序法", [&](vector<int>& nums, int k) {
            return solution.findKthLargest_sort(nums, k);
        }},
        {"最小堆", [&](vector<int>& nums, int k) {
            return solution.findKthLargest_heap(nums, k);
        }},
        {"快速选择", [&](vector<int>& nums, int k) {
            return solution.findKthLargest_quickselect(nums, k);
        }}
    };

    for (const auto& method_pair : methods) {
        const string& method_name = method_pair.first;
        const auto& method = method_pair.second;

        cout << "\n" << string(60, '=') << "\n";
        cout << "测试方法: " << method_name << "\n";
        cout << string(60, '=') << "\n";

        int passed = 0;
        int failed = 0;

        for (size_t i = 0; i < test_cases.size(); i++) {
            const auto& test_case = test_cases[i];
            vector<int> nums = test_case.nums;  // 复制数组
            int k = test_case.k;
            int expected = test_case.expected;

            try {
                int result = method(nums, k);

                if (result == expected) {
                    cout << "✓ 测试 " << (i + 1) << " 通过\n";
                    cout << "  输入: [";
                    for (size_t j = 0; j < test_case.nums.size(); j++) {
                        cout << test_case.nums[j];
                        if (j < test_case.nums.size() - 1) cout << ", ";
                    }
                    cout << "], k=" << k << "\n";
                    cout << "  输出: " << result << ", 期望: " << expected << "\n";
                    passed++;
                } else {
                    cout << "✗ 测试 " << (i + 1) << " 失败\n";
                    cout << "  输入: [";
                    for (size_t j = 0; j < test_case.nums.size(); j++) {
                        cout << test_case.nums[j];
                        if (j < test_case.nums.size() - 1) cout << ", ";
                    }
                    cout << "], k=" << k << "\n";
                    cout << "  输出: " << result << ", 期望: " << expected << "\n";
                    failed++;
                }
            } catch (const exception& e) {
                cout << "✗ 测试 " << (i + 1) << " 出现异常: " << e.what() << "\n";
                cout << "  输入: [";
                for (size_t j = 0; j < test_case.nums.size(); j++) {
                    cout << test_case.nums[j];
                    if (j < test_case.nums.size() - 1) cout << ", ";
                }
                cout << "], k=" << k << "\n";
                failed++;
            }
        }

        cout << string(60, '-') << "\n";
        cout << "测试结果: " << passed << " 通过, " << failed << " 失败\n";
        cout << string(60, '-') << "\n";

        if (failed == 0) {
            cout << "✓ " << method_name << " 所有测试通过!\n";
        }
    }

    cout << "\n" << string(60, '=') << "\n";
    cout << "所有测试完成!\n";
    cout << string(60, '=') << "\n";
}

int main() {
    test_solution();
    return 0;
}
