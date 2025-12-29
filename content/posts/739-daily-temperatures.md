---
title: "739. 每日温度"
difficulty: "中等"
description: "给定一个整数数组 temperatures，表示每天的温度，返回一个数组 answer，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。"
---

# 739. 每日温度

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个整数数组 `temperatures`，表示每天的温度，返回一个数组 `answer`，其中 `answer[i]` 是指对于第 `i` 天，下一个更高温度出现在几天后。如果其后没有更高的温度，该位置置 `0`。

## 示例

### 示例 1

- **输入：** `temperatures = [73,74,75,71,69,72,76,73]`
- **输出：** `[1,1,4,2,1,1,0,0]`

### 示例 2

- **输入：** `temperatures = [30,40,50,60]`
- **输出：** `[1,1,1,0]`

### 示例 3

- **输入：** `temperatures = [30,60,90]`
- **输出：** `[1,1,0]`

## 提示

- `1 <= temperatures.length <= 10^5`
- `30 <= temperatures[i] <= 100`

---

## 解法一：暴力解

### 思路

对于每一天，向后遍历找到第一个比它温度高的天数。

### Python

```python
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        answer = [0] * n

        for i in range(n):
            for j in range(i + 1, n):
                if temperatures[j] > temperatures[i]:
                    answer[i] = j - i
                    break

        return answer
```

### C++

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    answer[i] = j - i;
                    break;
                }
            }
        }

        return answer;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n²)
- **空间复杂度：** O(1)，除结果数组外

---

## 解法二：单调栈（推荐）

### 思路

使用**单调递减栈**，栈中存储温度的索引。

<Mermaid>
graph TB
    subgraph 单调栈处理流程
        A["遍历温度数组"] --> B{"栈不为空且<br/>当前温度 > 栈顶温度"}
        B -->|是| C["弹出栈顶索引<br/>计算天数差"]
        C --> B
        B -->|否| D["当前索引入栈"]
        D --> E["继续下一个"]
    end
</Mermaid>

**核心思想：**
- 维护一个单调递减栈（存索引）
- 当遇到比栈顶温度高的元素时，说明找到了栈顶元素下一个更高温度的天
- 弹出栈顶并计算天数差

**示例演示：** `temperatures = [73,74,75,71,69,72,76,73]`

<Mermaid>
graph TB
    subgraph 处理过程
        A1["i=0, temp=73<br/>栈: [0]"]
        A2["i=1, temp=74 > 73<br/>弹出0, answer[0]=1<br/>栈: [1]"]
        A3["i=2, temp=75 > 74<br/>弹出1, answer[1]=1<br/>栈: [2]"]
        A4["i=3, temp=71 < 75<br/>栈: [2,3]"]
        A5["i=4, temp=69 < 71<br/>栈: [2,3,4]"]
        A6["i=5, temp=72 > 69<br/>弹出4, answer[4]=1<br/>72 > 71, 弹出3, answer[3]=2<br/>栈: [2,5]"]
        A7["i=6, temp=76 > 72<br/>弹出5, answer[5]=1<br/>76 > 75, 弹出2, answer[2]=4<br/>栈: [6]"]
        A8["i=7, temp=73 < 76<br/>栈: [6,7]"]
    end
</Mermaid>

### Python

```python
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        answer = [0] * n
        stack = []  # 单调递减栈，存储索引

        for i, temp in enumerate(temperatures):
            # 当栈不为空且当前温度 > 栈顶温度
            while stack and temp > temperatures[stack[-1]]:
                prev_index = stack.pop()
                answer[prev_index] = i - prev_index
            stack.append(i)

        return answer
```

### C++

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
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
```

### 复杂度分析

- **时间复杂度：** O(n)，每个元素最多入栈出栈各一次
- **空间复杂度：** O(n)，栈的最大空间

---

## 解法三：从右向左遍历

### 思路

从数组末尾向左遍历，维护一个记录每个温度出现位置的数组。由于温度范围有限（30-100），可以用一个大小为 71 的数组记录每个温度最近出现的位置。

### Python

```python
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        answer = [0] * n
        # 记录每个温度下一次出现的位置，初始化为无穷大
        next_temp = [float('inf')] * 101

        for i in range(n - 1, -1, -1):
            # 查找比当前温度高的所有温度中，最近出现的位置
            min_day = min(next_temp[t] for t in range(temperatures[i] + 1, 101))
            if min_day != float('inf'):
                answer[i] = min_day - i
            # 更新当前温度的位置
            next_temp[temperatures[i]] = i

        return answer
```

### C++

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        vector<int> nextTemp(101, INT_MAX);

        for (int i = n - 1; i >= 0; i--) {
            int minDay = INT_MAX;
            // 查找比当前温度高的所有温度中，最近出现的位置
            for (int t = temperatures[i] + 1; t <= 100; t++) {
                minDay = min(minDay, nextTemp[t]);
            }
            if (minDay != INT_MAX) {
                answer[i] = minDay - i;
            }
            nextTemp[temperatures[i]] = i;
        }

        return answer;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n × C)，其中 C 是温度范围（71）
- **空间复杂度：** O(C)

---

## 三种解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 暴力解 | O(n²) | O(1) | 思路简单 | 时间复杂度高，超时 |
| 单调栈 | O(n) | O(n) | 时间最优，经典模板 | 需要额外栈空间 |
| 从右向左 | O(n×C) | O(C) | 温度范围小时很快 | 依赖温度范围限制 |

## 总结

- **必须掌握：** 单调栈是解决此类"下一个更大元素"问题的经典方法
- **模板记忆：** 单调递减栈 + 遍历时弹出计算
- **扩展应用：** 类似题目包括 496. 下一个更大元素 I、503. 下一个更大元素 II
