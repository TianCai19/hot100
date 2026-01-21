"""
146. LRU 缓存
https://leetcode.com/problems/lru-cache/
"""

from typing import Optional


class Node:
    def __init__(self, key: int, value: int):
        self.key = key
        self.value = value
        self.prev: Optional['Node'] = None
        self.next: Optional['Node'] = None


class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _add(self, node: Node) -> None:
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def _remove(self, node: Node) -> None:
        node.prev.next = node.next
        node.next.prev = node.prev

    def _move_to_head(self, node: Node) -> None:
        self._remove(node)
        self._add(node)

    def _pop_tail(self) -> Node:
        node = self.tail.prev
        self._remove(node)
        return node

    def get(self, key: int) -> int:
        node = self.cache.get(key)
        if not node:
            return -1
        self._move_to_head(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        node = self.cache.get(key)
        if node:
            node.value = value
            self._move_to_head(node)
            return

        new_node = Node(key, value)
        self.cache[key] = new_node
        self._add(new_node)

        if len(self.cache) > self.capacity:
            tail = self._pop_tail()
            del self.cache[tail.key]


def test_solution() -> None:
    cache = LRUCache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    assert cache.get(1) == 1
    cache.put(3, 3)
    assert cache.get(2) == -1
    cache.put(4, 4)
    assert cache.get(1) == -1
    assert cache.get(3) == 3
    assert cache.get(4) == 4

    cache = LRUCache(1)
    cache.put(2, 1)
    assert cache.get(2) == 1
    cache.put(3, 2)
    assert cache.get(2) == -1
    assert cache.get(3) == 2

    print("all tests passed")


if __name__ == "__main__":
    test_solution()
