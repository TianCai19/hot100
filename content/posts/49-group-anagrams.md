---
title: "49. 字母异位词分组"
difficulty: "中等"
description: "给你一个字符串数组，请你将字母异位词组合在一起。字母异位词是由重新排列源单词的所有字母得到的新单词。"
---

# 49. 字母异位词分组

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个字符串数组，请你将字母异位词组合在一起。字母异位词是由重新排列源单词的所有字母得到的新单词。

可以按任意顺序返回答案。

### 示例

```text
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]
```

```text
输入: strs = [""]
输出: [[""]]
```

```text
输入: strs = ["a"]
输出: [["a"]]
```

## 解法一：哈希表分组（推荐）

### 思路

字母异位词的特点是它们包含的字母相同，只是排列顺序不同。我们可以利用这个特点进行分组：

1. 对每个字符串的字符进行排序，排序后的字符串作为 key
2. 使用哈希表存储：key 为排序后的字符串，value 为原字符串列表
3. 遍历所有字符串，将它们放入对应的分组中
4. 返回哈希表中的所有值

### Python

```python
from typing import List
from collections import defaultdict

def group_anagrams(strs: List[str]) -> List[List[str]]:
    """
    哈希表分组解法

    时间复杂度: O(n*k*log(k))，其中 n 是字符串数量，k 是字符串最大长度
    空间复杂度: O(n*k)，存储所有字符串
    """
    if not strs:
        return []

    # 使用 defaultdict，自动创建空列表
    groups = defaultdict(list)

    for s in strs:
        # 对字符串排序，排序后的字符串作为 key
        sorted_str = ''.join(sorted(s))
        groups[sorted_str].append(s)

    return list(groups.values())

# 测试
if __name__ == "__main__":
    strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    print(group_anagrams(strs))
    # 输出: [['eat', 'tea', 'ate'], ['tan', 'nat'], ['bat']]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if (strs.empty()) {
            return {};
        }

        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& group : groups) {
            result.push_back(move(group.second));
        }

        return result;
    }
};

// 测试
int main() {
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    Solution solution;
    vector<vector<string>> result = solution.groupAnagrams(strs);

    for (const auto& group : result) {
        cout << "[";
        for (size_t i = 0; i < group.size(); i++) {
            cout << "\"" << group[i] << "\"";
            if (i < group.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
```

## 解法二：计数法

### 思路

使用字符计数代替排序，提高性能：

1. 创建每个字符串的字符计数（26个字母）
2. 使用计数向量作为 key（转为字符串便于哈希）
3. 同样使用哈希表进行分组

### Python

```python
def group_anagrams_count(strs: List[str]) -> List[List[str]]:
    """
    计数法解法（优化）

    时间复杂度: O(n*k)，其中 n 是字符串数量，k 是字符串最大长度
    空间复杂度: O(n*k)
    """
    if not strs:
        return []

    groups = defaultdict(list)

    for s in strs:
        # 统计每个字符出现的次数
        count = [0] * 26
        for char in s:
            count[ord(char) - ord('a')] += 1

        # 将计数数组转换为元组作为 key
        key = tuple(count)
        groups[key].append(s)

    return list(groups.values())
```

### C++

```cpp
vector<vector<string>> groupAnagramsCount(vector<string>& strs) {
    if (strs.empty()) {
        return {};
    }

    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        // 将计数数组转换为字符串作为 key
        string key;
        for (int cnt : count) {
            key += to_string(cnt) + '#';
        }

        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& group : groups) {
        result.push_back(move(group.second));
    }

    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 排序法 | O(n*k*log(k)) | O(n*k) | 直观易懂，代码简洁 |
| 计数法 | O(n*k) | O(n*k) | 性能更优，适合大数据集 |

**说明**：
- n：字符串数量
- k：字符串平均长度
- 排序法：对每个字符串排序，排序时间 O(k*log(k))
- 计数法：只统计字符，时间 O(k)，更适合大数据集

## 总结

- **哈希表**是解决分组问题的经典方法
- **排序法**直观易懂，适合小规模数据
- **计数法**性能更优，是实际生产环境中的首选
- 两种方法的核心思想都是将字母异位词映射到相同的 key
