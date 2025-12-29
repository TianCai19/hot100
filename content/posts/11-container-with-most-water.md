---
title: "盛最多水的容器"
difficulty: "中等"
description: "给你一个长度为 n 的整数数组 height。有 n 条垂直线，第 i 条线的两端点是 (i, 0) 和 (i, height[i])。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。"
---

# 11. 盛最多水的容器

<DifficultyBadge difficulty="中等" />

## 题目描述

给你一个长度为 `n` 的整数数组 `height`。有 `n` 条垂直线，第 `i` 条线的两端点是 `(i, 0)` 和 `(i, height[i])`。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以**容纳最多的水**。

**示例 1：**

```
输入: height = [1,8,6,2,5,4,8,3,7]
输出: 49
解释: 垂直线组成容器的最大面积是 49
```

**示例 2：**

```
输入: height = [1,1]
输出: 1
```

**示例 3：**

```
输入: height = [4,3,2,1,4]
输出: 16
```

## 解题思路

这是**双指针**的经典题目！

### 解法：双指针

使用两个指针分别指向数组的两端，向中间移动：

1. **左右指针**分别指向数组的左右两端
2. 计算当前面积：`area = min(height[left], height[right]) * (right - left)`
3. 移动**较短**的那条边（因为面积受限于较短的边）
4. 更新最大面积
5. 重复直到左右指针相遇

**为什么移动较短的边？**

- 面积受限于较短的边
- 即使移动较长的边，面积也不会增加（高度还是由较短的边决定）
- 移动较短的边，可能找到更高的边，从而增加面积

**时间复杂度：** O(n)
**空间复杂度：** O(1)

## 可视化示例

{<svg width="700" height="300" xmlns="http://www.w3.org/2000/svg">
  <text x="20" y="30" fontFamily="Arial" fontSize="14" fill="#fff">高度: [1, 8, 6, 2, 5, 4, 8, 3, 7]</text>
  <text x="20" y="50" fontFamily="Arial" fontSize="14" fill="#fff">索引:  0   1   2   3   4   5   6   7   8</text>

  <text x="20" y="90" fontFamily="Arial" fontSize="12" fill="#3b82f6">初始: 左=0(高度=1), 右=8(高度=7)</text>
  <text x="20" y="110" fontFamily="Arial" fontSize="12" fill="#3b82f6">面积 = min(1,7) * 8 = 8</text>
  <text x="20" y="130" fontFamily="Arial" fontSize="12" fill="#3b82f6">移动短边: 左指针</text>

  <text x="20" y="170" fontFamily="Arial" fontSize="12" fill="#10b981">左=1(高度=8), 右=8(高度=7)</text>
  <text x="20" y="190" fontFamily="Arial" fontSize="12" fill="#10b981">面积 = min(8,7) * 7 = 49</text>
  <text x="20" y="210" fontFamily="Arial" fontSize="12" fill="#10b981">移动短边: 右指针</text>

  <text x="400" y="150" fontFamily="Arial" fontSize="16" fill="#fff">最大面积: 49</text>
  <text x="400" y="180" fontFamily="Arial" fontSize="14" fill="#ccc">由索引1和8组成</text>

  <rect x="50" y="240" width="30" height="40" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="130" y="160" width="30" height="120" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="250" y="180" width="30" height="100" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="290" y="220" width="30" height="60" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="370" y="190" width="30" height="90" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="410" y="200" width="30" height="80" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="490" y="160" width="30" height="120" fill="#ef4444" stroke="#fff" strokeWidth="2"/>
  <rect x="530" y="210" width="30" height="70" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
  <rect x="610" y="170" width="30" height="110" fill="#8b5cf6" stroke="#fff" strokeWidth="1"/>
</svg>}

## 代码实现

### Python 实现

```python
def max_area(height: list[int]) -> int:
    """
    解法：双指针
    时间复杂度：O(n)
    空间复杂度：O(1)
    """
    left = 0
    right = len(height) - 1
    max_area = 0

    while left < right:
        # 计算当前面积
        current_area = min(height[left], height[right]) * (right - left)
        # 更新最大面积
        max_area = max(max_area, current_area)

        # 移动较短的那条边
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1

    return max_area

# 测试用例
if __name__ == "__main__":
    # 示例1
    height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    result1 = max_area(height1)
    print(f"示例1: height = {height1}")
    print(f"输出: {result1}")  # 49

    # 示例2
    height2 = [1, 1]
    result2 = max_area(height2)
    print(f"\n示例2: height = {height2}")
    print(f"输出: {result2}")  # 1

    # 示例3
    height3 = [4, 3, 2, 1, 4]
    result3 = max_area(height3)
    print(f"\n示例3: height = {height3}")
    print(f"输出: {result3}")  # 16

    # 额外测试
    height4 = [1, 2, 1]
    result4 = max_area(height4)
    print(f"\n额外测试: height = {height4}")
    print(f"输出: {result4}")  # 2

    height5 = [2, 3, 4, 5, 18, 17, 6]
    result5 = max_area(height5)
    print(f"\n额外测试: height = {height5}")
    print(f"输出: {result5}")  # 17
```

### C++ 实现

```cpp
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
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 暴力枚举 | O(n²) | O(1) | 思路简单，性能较差 |
| 双指针 | O(n) | O(1) | **最优解**，巧妙且高效 |

## 关键总结

- **双指针**是解决区间问题的强大技巧
- 关键在于**移动较短边**的决策
- 这是**贪心算法**的典型应用
- 类似的题目：接雨水、盛最多水的容器 II 等