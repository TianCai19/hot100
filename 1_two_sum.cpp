#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 解法二：哈希表优化
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash_map;  // 存储 {数值: 索引}

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        if (hash_map.find(complement) != hash_map.end()) {
            return {hash_map[complement], i};
        }

        hash_map[nums[i]] = i;
    }

    return {};
}

// 辅助函数：打印数组
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// 测试用例
int main() {
    // 示例1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    cout << "示例1: nums = [2, 7, 11, 15], target = 9" << endl;
    cout << "输出: ";
    printVector(twoSum(nums1, target1));
    cout << endl << endl;

    // 示例2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    cout << "示例2: nums = [3, 2, 4], target = 6" << endl;
    cout << "输出: ";
    printVector(twoSum(nums2, target2));
    cout << endl << endl;

    // 示例3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    cout << "示例3: nums = [3, 3], target = 6" << endl;
    cout << "输出: ";
    printVector(twoSum(nums3, target3));
    cout << endl << endl;

    // 额外测试
    vector<int> nums4 = {1, 2, 3, 4, 5};
    int target4 = 8;
    cout << "额外测试: nums = [1, 2, 3, 4, 5], target = 8" << endl;
    cout << "输出: ";
    printVector(twoSum(nums4, target4));
    cout << endl;

    return 0;
}
