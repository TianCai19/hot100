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
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) {
            return nullptr;
        }

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }

        if (!fast || !fast->next) {
            return nullptr;
        }

        ListNode *finder = head;
        while (finder != slow) {
            finder = finder->next;
            slow = slow->next;
        }

        return finder;
    }
};

pair<ListNode*, ListNode*> buildCycleList(const vector<int>& values, int pos) {
    if (values.empty()) {
        return {nullptr, nullptr};
    }

    vector<ListNode*> nodes;
    nodes.reserve(values.size());
    for (int val : values) {
        nodes.push_back(new ListNode(val));
    }

    for (size_t i = 0; i + 1 < nodes.size(); ++i) {
        nodes[i]->next = nodes[i + 1];
    }

    ListNode* entry = nullptr;
    if (pos != -1) {
        entry = nodes[pos];
        nodes.back()->next = entry;
    }

    return {nodes[0], entry};
}

int main() {
    Solution solution;

    {
        auto [head, entry] = buildCycleList({3, 2, 0, -4}, 1);
        ListNode* result = solution.detectCycle(head);
        assert(result == entry);
    }

    {
        auto [head, entry] = buildCycleList({1, 2}, 0);
        ListNode* result = solution.detectCycle(head);
        assert(result == entry);
    }

    {
        auto [head, entry] = buildCycleList({1}, -1);
        ListNode* result = solution.detectCycle(head);
        assert(result == entry);
    }

    {
        auto [head, entry] = buildCycleList({1, 2, 3, 4, 5}, 2);
        ListNode* result = solution.detectCycle(head);
        assert(result == entry);
    }

    cout << "all tests passed" << endl;
    return 0;
}
