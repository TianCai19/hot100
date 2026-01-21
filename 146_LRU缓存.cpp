#include <iostream>
#include <unordered_map>
#include <cassert>
using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    explicit LRUCache(int capacity) : capacity_(capacity) {
        head_ = new Node(0, 0);
        tail_ = new Node(0, 0);
        head_->next = tail_;
        tail_->prev = head_;
    }

    int get(int key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            return -1;
        }
        Node* node = it->second;
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
            return;
        }

        Node* node = new Node(key, value);
        cache_[key] = node;
        addNode(node);

        if ((int)cache_.size() > capacity_) {
            Node* tail = popTail();
            cache_.erase(tail->key);
            delete tail;
        }
    }

private:
    int capacity_;
    unordered_map<int, Node*> cache_;
    Node* head_;
    Node* tail_;

    void addNode(Node* node) {
        node->prev = head_;
        node->next = head_->next;
        head_->next->prev = node;
        head_->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    Node* popTail() {
        Node* node = tail_->prev;
        removeNode(node);
        return node;
    }
};

int main() {
    {
        LRUCache cache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        assert(cache.get(1) == 1);
        cache.put(3, 3);
        assert(cache.get(2) == -1);
        cache.put(4, 4);
        assert(cache.get(1) == -1);
        assert(cache.get(3) == 3);
        assert(cache.get(4) == 4);
    }

    {
        LRUCache cache(1);
        cache.put(2, 1);
        assert(cache.get(2) == 1);
        cache.put(3, 2);
        assert(cache.get(2) == -1);
        assert(cache.get(3) == 2);
    }

    cout << "all tests passed" << endl;
    return 0;
}
