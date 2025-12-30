---
title: "70. 爬楼梯"
difficulty: "简单"
description: "假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶？"
---

# 70. 爬楼梯

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

假设你正在爬楼梯。需要 `n` 阶你才能到达楼顶。

每次你可以爬 `1` 或 `2` 个台阶。你有多少种不同的方法可以爬到楼顶？

### 示例

```text
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶：
1. 1 阶 + 1 阶
2. 2 阶
```

```text
输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶：
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
```

## 解法一：动态规划（推荐）

### 思路

这是一个经典的动态规划问题。观察规律：
- 当 n = 1 时，只有 1 种方法：爬 1 阶
- 当 n = 2 时，有 2 种方法：爬 1+1 阶 或 爬 2 阶
- 当 n = 3 时，有 3 种方法：1+1+1、1+2、2+1
- 当 n = 4 时，有 5 种方法：1+1+1+1、1+1+2、1+2+1、2+1+1、2+2

可以看出，这是一个**斐波那契数列**：
- dp[i] = dp[i-1] + dp[i-2]

动态规划步骤：
1. 定义状态：dp[i] 表示爬到第 i 阶的方法数
2. 初始化：dp[1] = 1, dp[2] = 2
3. 状态转移：dp[i] = dp[i-1] + dp[i-2]（i >= 3）
4. 返回结果：dp[n]

### Python

```python
def climb_stairs(n: int) -> int:
    """
    动态规划解法

    时间复杂度: O(n)
    空间复杂度: O(1) - 只需要两个变量
    """
    if n <= 2:
        return n

    # 只保存前两个状态
    prev = 1  # dp[i-2]
    curr = 2  # dp[i-1]

    for i in range(3, n + 1):
        total = prev + curr  # dp[i] = dp[i-1] + dp[i-2]
        prev = curr
        curr = total

    return curr
```

### C++

```cpp
#include <iostream>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        /**
         * 动态规划解法
         *
         * 时间复杂度: O(n)
         * 空间复杂度: O(1)
         */
        if (n <= 2) {
            return n;
        }

        // 只保存前两个状态
        int prev = 1;  // dp[i-2]
        int curr = 2;  // dp[i-1]

        for (int i = 3; i <= n; i++) {
            int total = prev + curr;  // dp[i] = dp[i-1] + dp[i-2]
            prev = curr;
            curr = total;
        }

        return curr;
    }
};

// 测试函数
int main() {
    Solution s;

    cout << "n=2: " << s.climbStairs(2) << " (expected: 2)" << endl;
    cout << "n=3: " << s.climbStairs(3) << " (expected: 3)" << endl;
    cout << "n=4: " << s.climbStairs(4) << " (expected: 5)" << endl;
    cout << "n=5: " << s.climbStairs(5) << " (expected: 8)" << endl;

    return 0;
}
```

## 解法二：斐波那契数列公式

### 思路

使用斐波那契数列的通项公式：
F(n) = (φ^n - (-φ)^(-n)) / √5
其中 φ = (1 + √5) / 2

这种方法时间复杂度为 O(log n)，通过矩阵快速幂或公式计算实现。

### Python

```python
import math

def climb_stairs_formula(n: int) -> int:
    """
    斐波那契公式解法

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    # 黄金分割比
    phi = (1 + math.sqrt(5)) / 2

    # 使用公式计算
    return int((phi ** n - (-phi) ** (-n)) / math.sqrt(5))
```

### C++

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    int climbStairsFormula(int n) {
        /**
         * 斐波那契公式解法
         *
         * 时间复杂度: O(log n)
         * 空间复杂度: O(1)
         */
        const double phi = (1 + sqrt(5)) / 2;
        return int((pow(phi, n) - pow(-phi, -n)) / sqrt(5));
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(n) | O(1) | 直观易懂，推荐使用 |
| 公式解法 | O(log n) | O(1) | 数学解法，性能最好 |

## 总结

- 爬楼梯问题本质上是**斐波那契数列**
- 动态规划是最直观的解法，空间复杂度可优化至 O(1)
- 公式解法性能最好，但实现稍复杂
- 理解问题本质是解决此类问题的关键
