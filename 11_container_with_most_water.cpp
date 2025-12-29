#include <iostream>
#include <vector>
using namespace std;

int maxArea(vector<int>& height) {
    /**
     * 解法：双指针
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     */
    int left = 0;
    int right = height.size() - 1;
    int max_area = 0;

    while (left < right) {
        // 计算当前面积
        int current_area = min(height[left], height[right]) * (right - left);
        // 更新最大面积
        max_area = max(max_area, current_area);

        // 移动较短的那条边
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_area;
}

// 测试用例
int main() {
    // 示例1
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int result1 = maxArea(height1);
    cout << "示例1: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]" << endl;
    cout << "输出: " << result1 << endl;  // 49

    // 示例2
    vector<int> height2 = {1, 1};
    int result2 = maxArea(height2);
    cout << "\n示例2: height = [1, 1]" << endl;
    cout << "输出: " << result2 << endl;  // 1

    // 示例3
    vector<int> height3 = {4, 3, 2, 1, 4};
    int result3 = maxArea(height3);
    cout << "\n示例3: height = [4, 3, 2, 1, 4]" << endl;
    cout << "输出: " << result3 << endl;  // 16

    // 额外测试
    vector<int> height4 = {1, 2, 1};
    int result4 = maxArea(height4);
    cout << "\n额外测试: height = [1, 2, 1]" << endl;
    cout << "输出: " << result4 << endl;  // 2

    vector<int> height5 = {2, 3, 4, 5, 18, 17, 6};
    int result5 = maxArea(height5);
    cout << "\n额外测试: height = [2, 3, 4, 5, 18, 17, 6]" << endl;
    cout << "输出: " << result5 << endl;  // 17

    return 0;
}
