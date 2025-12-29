#include <iostream>
#include <vector>
using namespace std;

// 定义链表节点
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    /**
     * 解法：逐位相加 + 进位处理
     * 时间复杂度：O(max(m, n))，m 和 n 是两个链表的长度
     * 空间复杂度：O(max(m, n))
     */
    ListNode* dummy = new ListNode(0);  // 哑节点
    ListNode* current = dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry) {
        // 获取当前位的值（如果链表还有节点）
        int val1 = (l1 != nullptr) ? l1->val : 0;
        int val2 = (l2 != nullptr) ? l2->val : 0;

        // 计算当前位的和
        int total = val1 + val2 + carry;
        carry = total / 10;  // 计算进位

        // 创建新节点
        current->next = new ListNode(total % 10);
        current = current->next;

        // 移动到下一个节点
        if (l1 != nullptr) l1 = l1->next;
        if (l2 != nullptr) l2 = l2->next;
    }

    return dummy->next;
}

// 辅助函数：数组转链表
ListNode* listToLinkedList(const vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    return dummy->next;
}

// 辅助函数：链表转数组
vector<int> linkedListToList(ListNode* head) {
    vector<int> result;
    ListNode* current = head;
    while (current != nullptr) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    cout << "[";
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << ", ";
        current = current->next;
    }
    cout << "]" << endl;
}

// 测试用例
int main() {
    // 示例1: [2,4,3] + [5,6,4] = [7,0,8]
    ListNode* l1 = listToLinkedList({2, 4, 3});
    ListNode* l2 = listToLinkedList({5, 6, 4});
    ListNode* result1 = addTwoNumbers(l1, l2);
    cout << "示例1: ";
    printList(result1);  // [7, 0, 8]

    // 示例2: [0] + [0] = [0]
    l1 = listToLinkedList({0});
    l2 = listToLinkedList({0});
    ListNode* result2 = addTwoNumbers(l1, l2);
    cout << "示例2: ";
    printList(result2);  // [0]

    // 示例3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    l1 = listToLinkedList({9, 9, 9, 9, 9, 9, 9});
    l2 = listToLinkedList({9, 9, 9, 9});
    ListNode* result3 = addTwoNumbers(l1, l2);
    cout << "示例3: ";
    printList(result3);  // [8, 9, 9, 9, 0, 0, 0, 1]

    // 额外测试: 不同长度
    l1 = listToLinkedList({1, 2, 3});
    l2 = listToLinkedList({4, 5});
    ListNode* result4 = addTwoNumbers(l1, l2);
    cout << "额外测试: ";
    printList(result4);  // [5, 7, 3]

    return 0;
}
