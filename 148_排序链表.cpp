#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* mid = getMid(head);
        ListNode* right = mid->next;
        mid->next = nullptr;

        ListNode* leftSorted = sortList(head);
        ListNode* rightSorted = sortList(right);

        return merge(leftSorted, rightSorted);
    }

private:
    ListNode* getMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

ListNode* buildList(const vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }

    ListNode* head = new ListNode(values[0]);
    ListNode* node = head;
    for (size_t i = 1; i < values.size(); ++i) {
        node->next = new ListNode(values[i]);
        node = node->next;
    }
    return head;
}

vector<int> toVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

int main() {
    Solution solution;

    {
        ListNode* head = buildList({4, 2, 1, 3});
        ListNode* sorted = solution.sortList(head);
        assert(toVector(sorted) == vector<int>({1, 2, 3, 4}));
    }

    {
        ListNode* head = buildList({-1, 5, 3, 4, 0});
        ListNode* sorted = solution.sortList(head);
        assert(toVector(sorted) == vector<int>({-1, 0, 3, 4, 5}));
    }

    {
        ListNode* head = buildList({});
        ListNode* sorted = solution.sortList(head);
        assert(sorted == nullptr);
    }

    {
        ListNode* head = buildList({2, 1});
        ListNode* sorted = solution.sortList(head);
        assert(toVector(sorted) == vector<int>({1, 2}));
    }

    cout << "all tests passed" << endl;
    return 0;
}
