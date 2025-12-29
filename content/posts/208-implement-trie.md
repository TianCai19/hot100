---
title: "208. 实现 Trie（前缀树）"
difficulty: "中等"
description: "设计并实现一个 Trie（前缀树）类，用于高效地存储和检索字符串数据集中的键。"
---

# 208. 实现 Trie（前缀树）

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

Trie（发音类似 "try"）或者说 **前缀树** 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类，包含以下方法：
- `Trie()` - 初始化前缀树对象
- `insert(String word)` - 向前缀树中插入字符串 `word`
- `search(String word)` - 如果字符串 `word` 在前缀树中，返回 `true`（即，在检索之前已经插入）；否则，返回 `false`
- `startsWith(String prefix)` - 如果之前已经插入的字符串 `word` 的前缀之一为 `prefix`，返回 `true`；否则，返回 `false`

### 示例

```
输入：
["Trie", "insert", "search", "search", "startsWith", "search", "insert"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["apple"], ["app"]]

输出：
[null, null, true, false, true, true, null]

解释：
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
```

### 提示

- `1 <= word.length, prefix.length <= 2000`
- 最多调用 `2 × 10^4` 次 `insert`、`search` 和 `startsWith` 方法

---

## Trie 数据结构详解

### 什么是 Trie？

**Trie**（也称为前缀树或字典树）是一种特殊的树形数据结构，用于存储字符串集合。

**核心思想：** 将字符串的每个字符作为树的一个节点，字符串的公共前缀在树中共享节点。

### Trie 的结构

以插入 "apple" 和 "app" 为例：

```
root
 ├── a
     ├── p
         ├── p
         │   └── e (isWord)
         └── l (isWord)
```

**节点特点：**
- 每个节点包含：
  - `children` - 字符到子节点的映射（通常用哈希表或数组）
  - `isWord` - 标记该节点是否代表一个完整单词

### Trie 的优势

| 特性 | Trie | 哈希表 |
|------|------|--------|
| 插入时间 | O(m) | O(1) |
| 搜索时间 | O(m) | O(1) |
| 前缀搜索 | O(m) | O(n + m) |
| 空间效率 | 可共享前缀 | 独立存储 |
| 排序支持 | 自然排序 | 不支持 |

**m** = 字符串长度，**n** = 数据集大小

---

## 解法：标准 Trie 实现

### 思路

使用字典树（Trie）实现，每个节点包含：
1. `children` - 字典，映射字符到子节点
2. `is_word` - 布尔值，表示是否是完整单词

**操作说明：**

**插入 (insert)：**
1. 从根节点开始
2. 遍历字符，如果字符不在当前节点的子节点中，创建新节点
3. 移动到下一个节点
4. 遍历结束后，将最后一个节点标记为 `is_word = true`

**搜索 (search)：**
1. 从根节点开始
2. 遍历字符，如果字符不存在，返回 `false`
3. 遍历结束后，检查最后一个节点的 `is_word` 是否为 `true`
4. 返回结果

**前缀搜索 (startsWith)：**
1. 与搜索类似，但不需要检查 `is_word`
2. 只要所有字符都能在树中找到，就返回 `true`

### Python

```python
class TrieNode:
    """Trie 树节点"""
    def __init__(self):
        self.children = {}  # 字符到子节点的映射
        self.is_word = False  # 是否是完整单词

class Trie:
    def __init__(self):
        self.root = TrieNode()  # 根节点

    def insert(self, word: str) -> None:
        """
        插入字符串 word
        时间复杂度: O(m)，m 为字符串长度
        """
        node = self.root
        for char in word:
            # 如果字符不存在，创建新节点
            if char not in node.children:
                node.children[char] = TrieNode()
            # 移动到子节点
            node = node.children[char]
        # 标记完整单词
        node.is_word = True

    def search(self, word: str) -> bool:
        """
        搜索字符串 word
        时间复杂度: O(m)，m 为字符串长度
        """
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        # 检查是否是完整单词
        return node.is_word

    def startsWith(self, prefix: str) -> bool:
        """
        检查是否有以 prefix 为前缀的字符串
        时间复杂度: O(m)，m 为前缀长度
        """
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True
```

### C++

```cpp
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_word;

    TrieNode() : is_word(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    /** 插入字符串 word */
    void insert(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNode* node = root;
        for (char c : word) {
            // 如果字符不存在，创建新节点
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            // 移动到子节点
            node = node->children[c];
        }
        // 标记完整单词
        node->is_word = true;
    }

    /** 搜索字符串 word */
    bool search(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        // 检查是否是完整单词
        return node->is_word;
    }

    /** 检查是否有以 prefix 为前缀的字符串 */
    bool startsWith(string prefix) {
        /**
         * 时间复杂度: O(m)，m 为前缀长度
         */
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};
```

### 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 |
|------|-----------|-----------|
| 插入 (insert) | O(m) | O(m) |
| 搜索 (search) | O(m) | O(1) |
| 前缀搜索 (startsWith) | O(m) | O(1) |

**m** = 字符串/前缀长度

**空间复杂度说明：**
- 插入新字符串时，最坏情况下需要创建 m 个新节点
- 但 Trie 会共享公共前缀，所以实际空间小于所有字符串的总和

---

## 解法优化：数组实现

### 思路

使用固定大小的数组（26 个字母）代替哈希表，可以：
- 提高访问速度（O(1) 数组访问 vs O(1) 哈希表访问）
- 减少内存开销（避免哈希表的开销）
- 适合处理纯字母字符串

### Python

```python
class TrieNode:
    """使用数组实现的 Trie 节点"""
    def __init__(self):
        self.children = [None] * 26  # 26 个英文字母
        self.is_word = False

    def _char_to_index(self, char: str) -> int:
        """将字符转换为索引 (0-25)"""
        return ord(char) - ord('a')

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for char in word:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                node.children[idx] = TrieNode()
            node = node.children[idx]
        node.is_word = True

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                return False
            node = node.children[idx]
        return node.is_word

    def startsWith(self, prefix: str) -> bool:
        node = self.root
        for char in prefix:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                return False
            node = node.children[idx]
        return True
```

### C++

```cpp
class TrieNode {
public:
    TrieNode* children[26];
    bool is_word;

    TrieNode() : is_word(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->is_word = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return node->is_word;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }
};
```

### 复杂度分析

| 操作 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 哈希表实现 | O(m) | O(m) | 支持任意字符，代码简洁 | 有哈希表开销 |
| 数组实现 | O(m) | O(m) | 访问速度快，无哈希开销 | 只支持固定字符集 |

---

## Trie 的应用场景

### 1. 自动补全 (Autocomplete)

```python
def autocomplete(root: TrieNode, prefix: str) -> List[str]:
    """返回所有以 prefix 开头的单词"""
    # 首先定位到前缀位置
    node = root
    for char in prefix:
        if char not in node.children:
            return []
        node = node.children[char]

    # 深度优先搜索所有可能的单词
    results = []
    dfs(node, prefix, results)
    return results
```

### 2. 拼写检查 (Spell Checker)

```python
def spell_check(root: TrieNode, word: str) -> List[str]:
    """返回与 word 相似的单词（编辑距离为 1）"""
    # 遍历字典树，检查编辑距离
    suggestions = []
    # 实现略...
    return suggestions
```

### 3. IP 路由表

```python
class IPRouter:
    """使用 Trie 存储 IP 路由表"""
    def __init__(self):
        self.trie = Trie()

    def add_route(self, ip_prefix: str, next_hop: str):
        """添加路由规则"""
        self.trie.insert(ip_prefix)

    def lookup(self, ip: str) -> str:
        """查找最长匹配的前缀"""
        # 在 Trie 中查找最长匹配前缀
        return next_hop
```

---

## 总结

- **Trie** 是处理字符串前缀查询的经典数据结构
- **核心优势：** 高效的前缀搜索和自动补全
- **实现要点：** 节点结构、字符到子节点的映射、完整单词标记
- **应用广泛：** 搜索引擎、拼写检查、数据压缩、IP 路由等
- **优化选择：** 哈希表实现通用性好，数组实现性能更优
