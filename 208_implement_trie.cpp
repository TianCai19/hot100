/**
 * 208. 实现 Trie（前缀树）
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

/**
 * 解法一：哈希表实现的 Trie
 */
class TrieNodeHash {
public:
    unordered_map<char, TrieNodeHash*> children;
    bool is_word;

    TrieNodeHash() : is_word(false) {}
};

class TrieHash {
private:
    TrieNodeHash* root;

public:
    TrieHash() {
        root = new TrieNodeHash();
    }

    /** 插入字符串 word */
    void insert(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNodeHash* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNodeHash();
            }
            node = node->children[c];
        }
        node->is_word = true;
    }

    /** 搜索字符串 word */
    bool search(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNodeHash* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->is_word;
    }

    /** 检查是否有以 prefix 为前缀的字符串 */
    bool startsWith(string prefix) {
        /**
         * 时间复杂度: O(m)，m 为前缀长度
         */
        TrieNodeHash* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};

/**
 * 解法二：数组实现的 Trie
 */
class TrieNodeArray {
public:
    TrieNodeArray* children[26];
    bool is_word;

    TrieNodeArray() : is_word(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class TrieArray {
private:
    TrieNodeArray* root;

public:
    TrieArray() {
        root = new TrieNodeArray();
    }

    /** 插入字符串 word */
    void insert(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNodeArray* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNodeArray();
            }
            node = node->children[idx];
        }
        node->is_word = true;
    }

    /** 搜索字符串 word */
    bool search(string word) {
        /**
         * 时间复杂度: O(m)，m 为字符串长度
         */
        TrieNodeArray* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return node->is_word;
    }

    /** 检查是否有以 prefix 为前缀的字符串 */
    bool startsWith(string prefix) {
        /**
         * 时间复杂度: O(m)，m 为前缀长度
         */
        TrieNodeArray* node = root;
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

struct TestOperation {
    string operation;
    string arg;
    bool expected;
};

struct TestCase {
    string name;
    vector<TestOperation> operations;
};

template<typename TrieType>
void testTrie(const string& name, TrieType* trie) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "测试方法: " << name << "\n";
    cout << string(60, '=') << "\n";

    vector<TestCase> test_cases = {
        {
            "示例测试",
            {
                {"init", "", true},
                {"insert", "apple", true},
                {"search", "apple", true},
                {"search", "app", false},
                {"startsWith", "app", true},
                {"insert", "app", true},
                {"search", "app", true},
            }
        },
        {
            "前缀测试",
            {
                {"init", "", true},
                {"insert", "hello", true},
                {"insert", "hell", true},
                {"insert", "heaven", true},
                {"search", "hell", true},
                {"search", "hello", true},
                {"startsWith", "hea", true},
                {"startsWith", "he", true},
                {"startsWith", "hel", true},
            }
        },
        {
            "空字符串测试",
            {
                {"init", "", true},
                {"insert", "", true},
                {"search", "", true},
                {"startsWith", "", true},
            }
        },
        {
            "重复插入测试",
            {
                {"init", "", true},
                {"insert", "test", true},
                {"insert", "test", true},
                {"search", "test", true},
            }
        },
        {
            "多个单词测试",
            {
                {"init", "", true},
                {"insert", "cat", true},
                {"insert", "car", true},
                {"insert", "card", true},
                {"insert", "care", true},
                {"insert", "careful", true},
                {"search", "cat", true},
                {"search", "car", true},
                {"search", "card", true},
                {"search", "cake", false},
                {"startsWith", "ca", true},
                {"startsWith", "car", true},
                {"startsWith", "care", true},
            }
        }
    };

    for (const auto& test_case : test_cases) {
        cout << "\n" << string(60, '-') << "\n";
        cout << "测试用例: " << test_case.name << "\n";
        cout << string(60, '-') << "\n";

        bool all_passed = true;

        for (const auto& op : test_case.operations) {
            try {
                bool result;
                string status;

                if (op.operation == "init") {
                    result = true;
                    status = "✓";
                } else if (op.operation == "insert") {
                    trie->insert(op.arg);
                    result = true;
                    status = "✓";
                } else if (op.operation == "search") {
                    result = trie->search(op.arg);
                    status = (result == op.expected) ? "✓" : "✗";
                    if (result != op.expected) {
                        all_passed = false;
                    }
                } else if (op.operation == "startsWith") {
                    result = trie->startsWith(op.arg);
                    status = (result == op.expected) ? "✓" : "✗";
                    if (result != op.expected) {
                        all_passed = false;
                    }
                } else {
                    result = false;
                    status = "✗";
                }

                cout << status << " " << op.operation << "(" << op.arg << ") = "
                     << (result ? "true" : "false")
                     << " (期望: " << (op.expected ? "true" : "false") << ")\n";

            } catch (const exception& e) {
                cout << "✗ " << op.operation << "(" << op.arg << ") 出现异常: "
                     << e.what() << "\n";
                all_passed = false;
            }
        }

        if (all_passed) {
            cout << "\n✓ " << test_case.name << " 全部通过!\n";
        }
    }
}

int main() {
    cout << "=" << string(60, '=') << "\n";
    cout << "测试 Trie 数据结构\n";
    cout << string(60, '=') << "\n";

    // 测试哈希表实现
    TrieHash trie_hash;
    testTrie("哈希表实现", &trie_hash);

    // 测试数组实现
    TrieArray trie_array;
    testTrie("数组实现", &trie_array);

    cout << "\n" << string(60, '=') << "\n";
    cout << "所有测试完成!\n";
    cout << string(60, '=') << "\n";

    return 0;
}
