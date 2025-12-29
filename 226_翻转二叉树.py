from typing import Optional
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        """
        递归法：时间 O(n)，空间 O(h)
        翻转左右子树，然后交换左右子节点
        """
        if not root:
            return None

        # 递归翻转左右子树
        left = self.invertTree(root.left)
        right = self.invertTree(root.right)

        # 交换左右子节点
        root.left, root.right = right, left

        return root


# ==================== 测试代码 ====================

def build_tree(values):
    """根据列表构建二叉树，None 表示空节点"""
    if not values:
        return None

    root = TreeNode(values[0])
    queue = deque([root])
    i = 1

    while queue and i < len(values):
        node = queue.popleft()

        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1

        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1

    return root


def tree_to_list(root):
    """将二叉树转换为列表表示"""
    if not root:
        return []

    result = []
    queue = deque([root])

    while queue:
        node = queue.popleft()
        if node:
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
        else:
            result.append(None)

    # 移除末尾的 None
    while result and result[-1] is None:
        result.pop()

    return result


def test():
    solution = Solution()

    # 测试用例 1
    print("=" * 50)
    print("测试用例 1:")
    root1 = build_tree([4, 2, 7, 1, 3, 6, 9])
    print(f"原树: {tree_to_list(root1)}")
    result1 = solution.invertTree(root1)
    print(f"结果: {tree_to_list(result1)}")
    assert tree_to_list(result1) == [4, 7, 2, 9, 6, 3, 1], "测试用例 1 失败"
    print("✓ 通过")

    # 测试用例 2
    print("\n" + "=" * 50)
    print("测试用例 2:")
    root2 = build_tree([2, 1, 3])
    print(f"原树: {tree_to_list(root2)}")
    result2 = solution.invertTree(root2)
    print(f"结果: {tree_to_list(result2)}")
    assert tree_to_list(result2) == [2, 3, 1], "测试用例 2 失败"
    print("✓ 通过")

    # 测试用例 3: 空树
    print("\n" + "=" * 50)
    print("测试用例 3 (空树):")
    root3 = build_tree([])
    print(f"原树: {tree_to_list(root3)}")
    result3 = solution.invertTree(root3)
    print(f"结果: {tree_to_list(result3)}")
    assert tree_to_list(result3) == [], "测试用例 3 失败"
    print("✓ 通过")

    # 测试用例 4: 单节点
    print("\n" + "=" * 50)
    print("测试用例 4 (单节点):")
    root4 = build_tree([1])
    print(f"原树: {tree_to_list(root4)}")
    result4 = solution.invertTree(root4)
    print(f"结果: {tree_to_list(result4)}")
    assert tree_to_list(result4) == [1], "测试用例 4 失败"
    print("✓ 通过")

    print("\n" + "=" * 50)
    print("所有测试用例通过！")


if __name__ == "__main__":
    test()
