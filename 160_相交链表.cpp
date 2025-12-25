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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        /*
         * 双指针法：时间 O(m+n)，空间 O(1)
         * 两个指针分别从 A 和 B 出发，走完自己的链表后走对方的链表
         * 如果有交点会在交点相遇，没有交点会同时到达 nullptr
         */
        if (!headA || !headB) return nullptr;

        ListNode *pA = headA, *pB = headB;

        // 当 pA == pB 时停止（可能是交点，也可能同时为 nullptr）
        while (pA != pB) {
            pA = pA ? pA->next : headB;
            pB = pB ? pB->next : headA;
        }

        return pA;
    }
};

// ==================== 测试代码 ====================

// 构建两个相交的链表
pair<ListNode*, ListNode*> buildIntersectedLists(
    vector<int>& listA, vector<int>& listB, int skipA, int skipB) {

    if (listA.empty() || listB.empty()) return {nullptr, nullptr};

    // 创建链表 A 的独有部分
    ListNode dummyA(0);
    ListNode* currA = &dummyA;
    for (int i = 0; i < skipA; i++) {
        currA->next = new ListNode(listA[i]);
        currA = currA->next;
    }

    // 创建公共部分
    ListNode* commonHead = nullptr;
    if (skipA < (int)listA.size()) {
        commonHead = new ListNode(listA[skipA]);
        ListNode* curr = commonHead;
        for (int i = skipA + 1; i < (int)listA.size(); i++) {
            curr->next = new ListNode(listA[i]);
            curr = curr->next;
        }
        currA->next = commonHead;
    }

    // 创建链表 B 的独有部分并连接到公共部分
    ListNode dummyB(0);
    ListNode* currB = &dummyB;
    for (int i = 0; i < skipB; i++) {
        currB->next = new ListNode(listB[i]);
        currB = currB->next;
    }
    currB->next = commonHead;

    return {dummyA.next, dummyB.next};
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

    // 测试用例 1
    cout << "==================================================" << endl;
    cout << "测试用例 1:" << endl;
    vector<int> listA1 = {4, 1, 8, 4, 5};
    vector<int> listB1 = {5, 6, 1, 8, 4, 5};
    auto [headA1, headB1] = buildIntersectedLists(listA1, listB1, 2, 3);
    cout << "链表 A: "; printList(headA1);
    cout << "链表 B: "; printList(headB1);
    ListNode* result1 = solution.getIntersectionNode(headA1, headB1);
    if (result1) {
        cout << "结果: Intersected at '" << result1->val << "'" << endl;
    } else {
        cout << "结果: No intersection" << endl;
    }
    assert(result1 && result1->val == 8);
    cout << "✓ 通过" << endl;

    // 测试用例 2
    cout << "\n==================================================" << endl;
    cout << "测试用例 2:" << endl;
    vector<int> listA2 = {1, 9, 1, 2, 4};
    vector<int> listB2 = {3, 2, 4};
    auto [headA2, headB2] = buildIntersectedLists(listA2, listB2, 3, 1);
    cout << "链表 A: "; printList(headA2);
    cout << "链表 B: "; printList(headB2);
    ListNode* result2 = solution.getIntersectionNode(headA2, headB2);
    if (result2) {
        cout << "结果: Intersected at '" << result2->val << "'" << endl;
    } else {
        cout << "结果: No intersection" << endl;
    }
    assert(result2 && result2->val == 2);
    cout << "✓ 通过" << endl;

    // 测试用例 3: 无交点
    cout << "\n==================================================" << endl;
    cout << "测试用例 3 (无交点):" << endl;
    ListNode* headA3 = new ListNode(2);
    headA3->next = new ListNode(6);
    headA3->next->next = new ListNode(4);

    ListNode* headB3 = new ListNode(1);
    headB3->next = new ListNode(5);

    cout << "链表 A: "; printList(headA3);
    cout << "链表 B: "; printList(headB3);
    ListNode* result3 = solution.getIntersectionNode(headA3, headB3);
    if (result3) {
        cout << "结果: Intersected at '" << result3->val << "'" << endl;
    } else {
        cout << "结果: No intersection" << endl;
    }
    assert(result3 == nullptr);
    cout << "✓ 通过" << endl;

    cout << "\n==================================================" << endl;
    cout << "所有测试用例通过！" << endl;

    return 0;
}
