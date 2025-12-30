---
title: "136. 只出现一次的数字"
difficulty: "简单"
description: "给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现一次的元素。"
---

# 136. 只出现一次的数字

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现一次的元素。

你必须设计并实现线性时间复杂度的解决方案，并且可以使用常数级别的额外空间。

### 示例

```text
输入：nums = [2,2,1]
输出：1
```

```text
输入：nums = [4,1,2,1,2]
输出：4
```

```text
输入：nums = [1]
输出：1
```

## 解法一：异或运算（推荐）

### 思路

异或运算具有以下性质：
- `a ⊕ a = 0`：任何数与自身异或结果为 0
- `a ⊕ 0 = a`：任何数与 0 异或结果为自身
- 异或满足交换律和结合律：`a ⊕ b ⊕ a = (a ⊕ a) ⊕ b = 0 ⊕ b = b`

基于这些性质，数组中所有元素依次异或，最终结果就是只出现一次的元素。

### Python

```python
from typing import List

def single_number(nums: List[int]) -> int:
    """
    异或运算解法

    时间复杂度: O(n)，其中 n 是数组长度
    空间复杂度: O(1)
    """
    result = 0
    for num in nums:
        result ^= num
    return result
```

### C++

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
};
```

## 解法二：哈希集合

### 思路

使用哈希集合记录出现过的数字：
1. 遍历数组，如果数字不在集合中，则加入集合
2. 如果数字已在集合中，则移除该数字（说明是重复元素）
3. 最后集合中只剩下只出现一次的元素

### Python

```python
def single_number_hash(nums: List[int]) -> int:
    """
    哈希集合解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    seen = set()
    for num in nums:
        if num in seen:
            seen.remove(num)
        else:
            seen.add(num)
    return seen.pop()
```

### C++

```cpp
#include <unordered_set>
#include <vector>
using namespace std;

int singleNumberHash(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        auto it = seen.find(num);
        if (it != seen.end()) {
            seen.erase(it);
        } else {
            seen.insert(num);
        }
    }
    return *seen.begin();
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 异或运算 | O(n) | O(1) | 最优解，利用数学性质 |
| 哈希集合 | O(n) | O(n) | 直观易懂，但占用额外空间 |

## 总结

- **异或运算是最优解**，完美满足题目要求的时间复杂度和空间复杂度
- 异或的性质：自反性（`a ⊕ a = 0`）、单位性（`a ⊕ 0 = a`）、交换律和结合律
- 这种数学技巧体现了算法的优雅性
- 哈希集合解法虽然直观，但空间复杂度不满足常数级别的要求
