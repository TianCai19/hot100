#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        /*
         * 快慢指针 + 反转链表：时间 O(n)，空间 O(1)
         * 1. 用快慢指针找中点
         * 2. 反转后半部分链表
         * 3. 比较前后两半是否相同
         */
        // 第一步：用快慢指针找中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 第二步：反转后半部分链表
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }

        // 第三步：比较前后两半
        ListNode* left = head;
        ListNode* right = prev;
        bool result = true;
        while (right) {
            if (left->val != right->val) {
                result = false;
                break;
            }
            left = left->next;
            right = right->next;
        }

        return result;
    }
};

// ==================== 测试代码 ====================

// 根据数组构建链表
ListNode* buildList(vector<int>& vals) {
    if (vals.empty()) return nullptr;
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int val : vals) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    return dummy.next;
}

// 打印链表
void printList(ListNode* head) {
    if (!head) {
        cout << "Empty" << endl;
        return;
    }
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution solution;

    // 测试用例 1: 回文链表
    cout << "==================================================" << endl;
    cout << "测试用例 1:" << endl;
    vector<int> vals1 = {1, 2, 2, 1};
    ListNode* head1 = buildList(vals1);
    cout << "链表: "; printList(head1);
    bool result1 = solution.isPalindrome(head1);
    cout << "结果: " << (result1 ? "true" : "false") << endl;
    assert(result1 == true);
    cout << "✓ 通过" << endl;

    // 测试用例 2: 非回文链表
    cout << "\n==================================================" << endl;
    cout << "测试用例 2:" << endl;
    vector<int> vals2 = {1, 2};
    ListNode* head2 = buildList(vals2);
    cout << "链表: "; printList(head2);
    bool result2 = solution.isPalindrome(head2);
    cout << "结果: " << (result2 ? "true" : "false") << endl;
    assert(result2 == false);
    cout << "✓ 通过" << endl;

    // 测试用例 3: 单节点（回文）
    cout << "\n==================================================" << endl;
    cout << "测试用例 3 (单节点):" << endl;
    vector<int> vals3 = {1};
    ListNode* head3 = buildList(vals3);
    cout << "链表: "; printList(head3);
    bool result3 = solution.isPalindrome(head3);
    cout << "结果: " << (result3 ? "true" : "false") << endl;
    assert(result3 == true);
    cout << "✓ 通过" << endl;

    // 测试用例 4: 奇数长度回文
    cout << "\n==================================================" << endl;
    cout << "测试用例 4 (奇数长度回文):" << endl;
    vector<int> vals4 = {1, 2, 3, 2, 1};
    ListNode* head4 = buildList(vals4);
    cout << "链表: "; printList(head4);
    bool result4 = solution.isPalindrome(head4);
    cout << "结果: " << (result4 ? "true" : "false") << endl;
    assert(result4 == true);
    cout << "✓ 通过" << endl;

    // 测试用例 5: 非回文（奇数长度）
    cout << "\n==================================================" << endl;
    cout << "测试用例 5 (非回文):" << endl;
    vector<int> vals5 = {1, 2, 3, 4, 5};
    ListNode* head5 = buildList(vals5);
    cout << "链表: "; printList(head5);
    bool result5 = solution.isPalindrome(head5);
    cout << "结果: " << (result5 ? "true" : "false") << endl;
    assert(result5 == false);
    cout << "✓ 通过" << endl;

    cout << "\n==================================================" << endl;
    cout << "所有测试用例通过！" << endl;

    return 0;
}
