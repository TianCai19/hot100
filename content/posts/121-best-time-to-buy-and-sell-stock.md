---
title: "121. 买卖股票的最佳时机"
difficulty: "简单"
description: "给定一个数组 prices ，其中 prices[i] 表示股票第 i 天的价格。你只能选择某一天买入这只股票，并选择在未来的某一天卖出该股票。设计一个算法来计算你所能获得的最大利润。返回你能获得的最大利润。如果你不能获取任何利润，则返回 0。"
---

# 121. 买卖股票的最佳时机

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定一个数组 `prices`，其中 `prices[i]` 表示股票第 `i` 天的价格。

你只能选择某一天买入这只股票，并选择在未来的某一天卖出该股票。设计一个算法来计算你所能获得的最大利润。

返回你能获得的最大利润。如果你不能获取任何利润，则返回 `0`。

### 示例

```text
输入：prices = [7,1,5,3,6,4]
输出：5
解释：在第 2 天（价格 = 1）的时候买入，在第 5 天（价格 = 6）的时候卖出，最大利润 = 6-1 = 5
注意利润不能是 7-1 = 6, 因为卖出价格应该大于买入价格
```

```text
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0
```

## 解法一：一次遍历（推荐）

### 思路

维护两个变量：
1. `min_price`：记录遍历过程中的最小价格（买入点）
2. `max_profit`：记录当前的最大利润

遍历数组：
- 更新最小价格：`min_price = min(min_price, price)`
- 计算当前利润：`price - min_price`
- 更新最大利润：`max_profit = max(max_profit, current_profit)`

### Python

```python
from typing import List

def max_profit(prices: List[int]) -> int:
    """
    一次遍历解法

    时间复杂度: O(n)，其中 n 是价格数组的长度
    空间复杂度: O(1)，只使用了常数个变量
    """
    if not prices:
        return 0

    min_price = float('inf')  # 初始化为无穷大
    max_profit = 0

    for price in prices:
        # 更新最小价格
        if price < min_price:
            min_price = price

        # 计算当前利润并更新最大利润
        profit = price - min_price
        if profit > max_profit:
            max_profit = profit

    return max_profit

# 测试用例
if __name__ == "__main__":
    print(max_profit([7, 1, 5, 3, 6, 4]))  # 输出: 5
    print(max_profit([7, 6, 4, 3, 1]))      # 输出: 0
    print(max_profit([2, 4, 1]))            # 输出: 2
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int min_price = INT_MAX;  // 初始化为最大值
        int max_profit = 0;

        for (int price : prices) {
            // 更新最小价格
            if (price < min_price) {
                min_price = price;
            }

            // 计算当前利润并更新最大利润
            int profit = price - min_price;
            if (profit > max_profit) {
                max_profit = profit;
            }
        }

        return max_profit;
    }
};

// 测试用例
int main() {
    Solution solution;

    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << solution.maxProfit(prices1) << endl;  // 输出: 5

    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << solution.maxProfit(prices2) << endl;  // 输出: 0

    vector<int> prices3 = {2, 4, 1};
    cout << solution.maxProfit(prices3) << endl;  // 输出: 2

    return 0;
}
```

## 解法二：动态规划

### 思路

使用动态规划记录第 i 天之前的最小价格和最大利润：

状态定义：
- `dp[i][0]`：第 i 天不持有股票的最大利润
- `dp[i][1]`：第 i 天持有股票的最大利润

状态转移：
- 不持有股票：`max(dp[i-1][0], dp[i-1][1] + prices[i])`
- 持有股票：`max(dp[i-1][1], -prices[i])`

### Python

```python
def max_profit_dp(prices: List[int]) -> int:
    """
    动态规划解法

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    if not prices:
        return 0

    # dp0: 不持有股票的最大利润
    # dp1: 持有股票的最大利润
    dp0, dp1 = 0, -prices[0]

    for price in prices[1:]:
        dp0 = max(dp0, dp1 + price)
        dp1 = max(dp1, -price)

    return dp0
```

### C++

```cpp
int maxProfitDP(vector<int>& prices) {
    if (prices.empty()) {
        return 0;
    }

    int dp0 = 0;          // 不持有股票的最大利润
    int dp1 = -prices[0]; // 持有股票的最大利润

    for (size_t i = 1; i < prices.size(); i++) {
        dp0 = max(dp0, dp1 + prices[i]);
        dp1 = max(dp1, -prices[i]);
    }

    return dp0;
}
```

## 解法三：暴力解法

### 思路

遍历所有可能的买入和卖出组合，计算最大利润。

### Python

```python
def max_profit_brute(prices: List[int]) -> int:
    """
    暴力解法

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    if not prices:
        return 0

    max_profit = 0
    n = len(prices)

    for i in range(n):
        for j in range(i + 1, n):
            profit = prices[j] - prices[i]
            if profit > max_profit:
                max_profit = profit

    return max_profit
```

### C++

```cpp
int maxProfitBrute(vector<int>& prices) {
    if (prices.empty()) {
        return 0;
    }

    int max_profit = 0;
    int n = prices.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int profit = prices[j] - prices[i];
            if (profit > max_profit) {
                max_profit = profit;
            }
        }
    }

    return max_profit;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 一次遍历 | O(n) | O(1) | 最优解，推荐使用 |
| 动态规划 | O(n) | O(1) | 思想清晰，可扩展 |
| 暴力解法 | O(n^2) | O(1) | 思路直观，性能差 |

## 总结

- **一次遍历**是最优解，时间和空间复杂度都是最优的
- **动态规划**虽然复杂，但思想可以扩展到多次买卖股票问题
- **暴力解法**仅用于理解，实际应用中不可取
- 核心思想是维护遍历过程中的最小买入价格
