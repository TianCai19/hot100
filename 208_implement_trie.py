"""
208. 实现 Trie（前缀树）
https://leetcode.com/problems/implement-trie-prefix-tree/
"""

from typing import List, Dict


class TrieNode:
    """Trie 树节点 - 哈希表实现"""
    def __init__(self):
        self.children: Dict[str, 'TrieNode'] = {}
        self.is_word = False


class TrieHash:
    """使用哈希表实现的 Trie"""
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        """
        插入字符串 word
        时间复杂度: O(m)，m 为字符串长度
        """
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
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


class TrieNodeArray:
    """Trie 树节点 - 数组实现"""
    def __init__(self):
        self.children = [None] * 26
        self.is_word = False

    def _char_to_index(self, char: str) -> int:
        """将字符转换为索引 (0-25)"""
        return ord(char) - ord('a')


class TrieArray:
    """使用数组实现的 Trie"""
    def __init__(self):
        self.root = TrieNodeArray()

    def insert(self, word: str) -> None:
        """
        插入字符串 word
        时间复杂度: O(m)，m 为字符串长度
        """
        node = self.root
        for char in word:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                node.children[idx] = TrieNodeArray()
            node = node.children[idx]
        node.is_word = True

    def search(self, word: str) -> bool:
        """
        搜索字符串 word
        时间复杂度: O(m)，m 为字符串长度
        """
        node = self.root
        for char in word:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                return False
            node = node.children[idx]
        return node.is_word

    def startsWith(self, prefix: str) -> bool:
        """
        检查是否有以 prefix 为前缀的字符串
        时间复杂度: O(m)，m 为前缀长度
        """
        node = self.root
        for char in prefix:
            idx = node._char_to_index(char)
            if not node.children[idx]:
                return False
            node = node.children[idx]
        return True


def test_trie():
    """测试所有 Trie 实现"""
    print("=" * 60)
    print("测试 Trie 数据结构")
    print("=" * 60)

    test_cases = [
        {
            "name": "示例测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "apple", None),
                ("search", "apple", True),
                ("search", "app", False),
                ("startsWith", "app", True),
                ("insert", "app", None),
                ("search", "app", True),
            ]
        },
        {
            "name": "前缀测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "hello", None),
                ("insert", "hell", None),
                ("insert", "heaven", None),
                ("search", "hell", True),
                ("search", "hello", True),
                ("startsWith", "hea", True),
                ("startsWith", "he", True),
                ("startsWith", "hel", True),
            ]
        },
        {
            "name": "空字符串测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "", None),
                ("search", "", True),
                ("startsWith", "", True),
            ]
        },
        {
            "name": "重复插入测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "test", None),
                ("insert", "test", None),
                ("search", "test", True),
            ]
        },
        {
            "name": "多个单词测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "cat", None),
                ("insert", "car", None),
                ("insert", "card", None),
                ("insert", "care", None),
                ("insert", "careful", None),
                ("search", "cat", True),
                ("search", "car", True),
                ("search", "card", True),
                ("search", "cake", False),
                ("startsWith", "ca", True),
                ("startsWith", "car", True),
                ("startsWith", "care", True),
            ]
        },
        {
            "name": "数字和特殊字符测试",
            "operations": [
                ("Trie", "init", None),
                ("insert", "123", None),
                ("insert", "hello123", None),
                ("search", "123", True),
                ("search", "hello123", True),
                ("startsWith", "123", True),
            ]
        }
    ]

    trie_classes = [
        ("哈希表实现", TrieHash),
        ("数组实现", TrieArray)
    ]

    for trie_name, TrieClass in trie_classes:
        print(f"\n{'=' * 60}")
        print(f"测试方法: {trie_name}")
        print(f"{'=' * 60}")

        for test_case in test_cases:
            print(f"\n{'-' * 60}")
            print(f"测试用例: {test_case['name']}")
            print(f"{'-' * 60}")

            trie = None
            all_passed = True

            for operation, arg, expected in test_case['operations']:
                try:
                    if operation == "Trie":
                        trie = TrieClass()
                        result = "初始化成功"
                        status = "✓"
                    elif operation == "insert":
                        trie.insert(arg)
                        result = "插入成功"
                        status = "✓"
                    elif operation == "search":
                        result = trie.search(arg)
                        status = "✓" if result == expected else "✗"
                        if result != expected:
                            all_passed = False
                    elif operation == "startsWith":
                        result = trie.startsWith(arg)
                        status = "✓" if result == expected else "✗"
                        if result != expected:
                            all_passed = False
                    else:
                        status = "✗"
                        result = "未知操作"

                    print(f"{status} {operation}({arg}) = {result} (期望: {expected})")

                except Exception as e:
                    print(f"✗ {operation}({arg}) 出现异常: {e}")
                    all_passed = False

            if all_passed:
                print(f"\n✓ {test_case['name']} 全部通过!")

    print(f"\n{'=' * 60}")
    print("所有测试完成!")
    print(f"{'=' * 60}")


def test_trie_performance():
    """性能测试"""
    print("\n" + "=" * 60)
    print("性能测试")
    print("=" * 60)

    import time

    # 测试数据
    words = ["apple", "application", "apply", "app", "banana", "band", "bandana"] * 100
    search_words = ["apple", "app", "band", "ban", "cat", "application"] * 50

    for name, TrieClass in [("哈希表实现", TrieHash), ("数组实现", TrieArray)]:
        print(f"\n测试 {name}:")

        # 插入测试
        start_time = time.time()
        trie = TrieClass()
        for word in words:
            trie.insert(word)
        insert_time = time.time() - start_time
        print(f"  插入 {len(words)} 个单词: {insert_time:.4f} 秒")

        # 搜索测试
        start_time = time.time()
        for word in search_words:
            trie.search(word)
        search_time = time.time() - start_time
        print(f"  搜索 {len(search_words)} 次: {search_time:.4f} 秒")

        # 前缀搜索测试
        start_time = time.time()
        for prefix in search_words:
            trie.startsWith(prefix)
        prefix_time = time.time() - start_time
        print(f"  前缀搜索 {len(search_words)} 次: {prefix_time:.4f} 秒")


if __name__ == "__main__":
    test_trie()
    test_trie_performance()
