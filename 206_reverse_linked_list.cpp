/**
 * 206. 反转链表
 * https://leetcode.com/problems/reverse-linked-list/
 */

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/**
 * 链表节点定义
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    /**
     * 解法一：迭代法（双指针）
     */
    ListNode* reverseList_iterative(ListNode* head) {
        /**
         * 迭代法 - 双指针
         * 时间复杂度: O(n)，n 为链表长度
         * 空间复杂度: O(1)
         */
        ListNode* prev = nullptr;  // 前一个节点（反转后链表的头）
        ListNode* curr = head;     // 当前节点

        while (curr) {
            // 1. 保存下一个节点
            ListNode* next_temp = curr->next;

            // 2. 反转指针
            curr->next = prev;

            // 3. 移动指针
            prev = curr;
            curr = next_temp;
        }

        // prev 最终指向新的头节点
        return prev;
    }

    /**
     * 解法二：递归法
     */
    ListNode* reverseList_recursive(ListNode* head) {
        /**
         * 递归法
         * 时间复杂度: O(n)，n 为链表长度
         * 空间复杂度: O(n)，递归栈深度
         */
        // 基准条件：空链表或只有一个节点
        if (!head || !head->next) {
            return head;
        }

        // 递归处理子链表
        ListNode* new_head = reverseList_recursive(head->next);

        // 反转指针
        head->next->next = head;
        head->next = nullptr;

        return new_head;
    }
};

/**
 * 辅助函数
 */
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }

    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }

    return head;
}

vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    ListNode* current = head;
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

bool compareLinkedLists(ListNode* l1, ListNode* l2) {
    while (l1 && l2) {
        if (l1->val != l2->val) {
            return false;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == nullptr && l2 == nullptr;
}

void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

/**
 * 测试函数
 */
void testSolution(const string& name, ListNode* (Solution::*method)(ListNode*)) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "测试方法: " << name << "\n";
    cout << string(60, '=') << "\n";

    vector<vector<int>> test_cases = {
        {1, 2, 3, 4, 5},     // 示例1：5个节点
        {1, 2},              // 示例2：2个节点
        {},                  // 示例3：空链表
        {1},                 // 单个节点
        {1, 2, 3},           // 3个节点
        {1, 2, 3, 4},        // 4个节点
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},  // 10个节点
        {0, 0, 0, 0},        // 重复值
        {-1, -2, -3, -4},    // 负数
        {5, 3, 1, 2, 4}      // 乱序数组
    };

    vector<string> descriptions = {
        "示例1：5个节点",
        "示例2：2个节点",
        "示例3：空链表",
        "单个节点",
        "3个节点",
        "4个节点",
        "10个节点",
        "重复值",
        "负数",
        "乱序数组"
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < test_cases.size(); i++) {
        const auto& input = test_cases[i];
        const string& description = descriptions[i];

        // 计算期望输出（反转）
        vector<int> expected = input;
        reverse(expected.begin(), expected.end());

        try {
            // 创建输入链表
            ListNode* head = createLinkedList(input);

            // 执行反转
            Solution solution;
            ListNode* result_head = (solution.*method)(head);

            // 转换为向量
            vector<int> result = linkedListToVector(result_head);

            // 验证结果
            if (result == expected) {
                cout << "✓ 测试 " << (i + 1) << " 通过: " << description << "\n";
                cout << "  输入: [";
                for (size_t j = 0; j < input.size(); j++) {
                    cout << input[j];
                    if (j < input.size() - 1) cout << ", ";
                }
                cout << "]\n";
                cout << "  输出: [";
                for (size_t j = 0; j < result.size(); j++) {
                    cout << result[j];
                    if (j < result.size() - 1) cout << ", ";
                }
                cout << "]\n";
                passed++;
            } else {
                cout << "✗ 测试 " << (i + 1) << " 失败: " << description << "\n";
                cout << "  输入: [";
                for (size_t j = 0; j < input.size(); j++) {
                    cout << input[j];
                    if (j < input.size() - 1) cout << ", ";
                }
                cout << "]\n";
                cout << "  期望: [";
                for (size_t j = 0; j < expected.size(); j++) {
                    cout << expected[j];
                    if (j < expected.size() - 1) cout << ", ";
                }
                cout << "]\n";
                cout << "  实际: [";
                for (size_t j = 0; j < result.size(); j++) {
                    cout << result[j];
                    if (j < result.size() - 1) cout << ", ";
                }
                cout << "]\n";
                failed++;
            }

            // 清理内存
            deleteLinkedList(result_head);

        } catch (const exception& e) {
            cout << "✗ 测试 " << (i + 1) << " 出现异常: " << description << "\n";
            cout << "  异常: " << e.what() << "\n";
            failed++;
        }
    }

    cout << string(60, '-') << "\n";
    cout << "测试结果: " << passed << " 通过, " << failed << " 失败\n";
    cout << string(60, '-') << "\n";

    if (failed == 0) {
        cout << "✓ " << name << " 所有测试通过!\n";
    }
}

int main() {
    cout << "=" << string(60, '=') << "\n";
    cout << "测试反转链表\n";
    cout << string(60, '=') << "\n";

    // 测试迭代法
    testSolution("迭代法 (双指针)", &Solution::reverseList_iterative);

    // 测试递归法
    testSolution("递归法", &Solution::reverseList_recursive);

    cout << "\n" << string(60, '=') << "\n";
    cout << "所有测试完成!\n";
    cout << string(60, '=') << "\n";

    return 0;
}
