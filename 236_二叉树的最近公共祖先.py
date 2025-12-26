"""
236. 二叉树的最近公共祖先
https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
"""

from typing import Optional


class TreeNode:
    def __init__(self, x: int):
        self.val = x
        self.left: Optional['TreeNode'] = None
        self.right: Optional['TreeNode'] = None


class Solution:
    def lowestCommonAncestor_hash(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        """解法一：存储父节点 + 哈希表"""
        parent = {root: None}

        # BFS 记录所有节点的父节点
        stack = [root]
        while stack:
            node = stack.pop()
            if node.left:
                parent[node.left] = node
                stack.append(node.left)
            if node.right:
                parent[node.right] = node
                stack.append(node.right)

        # 记录 p 到根节点的路径
        ancestors = set()
        curr = p
        while curr:
            ancestors.add(curr)
            curr = parent[curr]

        # 找 q 的祖先中第一个在 p 路径上的节点
        curr = q
        while curr not in ancestors:
            curr = parent[curr]

        return curr

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        """解法二：递归（最优解）"""
        # 递归终止条件
        if not root or root == p or root == q:
            return root

        # 在左右子树中查找
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)

        # 如果左右都找到了，说明当前节点是 LCA
        if left and right:
            return root

        # 否则返回非空的那个
        return left if left else right


def build_tree(values: list) -> tuple:
    """从列表构建二叉树，返回 (root, nodes_dict)"""
    if not values:
        return None, {}

    nodes = {}
    root = TreeNode(values[0])
    nodes[values[0]] = root
    queue = [root]
    i = 1

    while queue and i < len(values):
        node = queue.pop(0)

        # 左子节点
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            nodes[values[i]] = node.left
            queue.append(node.left)
        i += 1

        # 右子节点
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            nodes[values[i]] = node.right
            queue.append(node.right)
        i += 1

    return root, nodes


def test():
    solution = Solution()

    # 测试用例 1: p=5, q=1, LCA=3
    root1, nodes1 = build_tree([3, 5, 1, 6, 2, 0, 8, None, None, 7, 4])
    p1, q1 = nodes1[5], nodes1[1]
    result1 = solution.lowestCommonAncestor(root1, p1, q1)
    assert result1.val == 3, f"测试1失败: 期望 3, 得到 {result1.val}"
    print(f"✓ 测试1通过: p=5, q=1, LCA={result1.val}")

    # 测试用例 2: p=5, q=4, LCA=5
    root2, nodes2 = build_tree([3, 5, 1, 6, 2, 0, 8, None, None, 7, 4])
    p2, q2 = nodes2[5], nodes2[4]
    result2 = solution.lowestCommonAncestor(root2, p2, q2)
    assert result2.val == 5, f"测试2失败: 期望 5, 得到 {result2.val}"
    print(f"✓ 测试2通过: p=5, q=4, LCA={result2.val}")

    # 测试用例 3: p=1, q=2, LCA=1
    root3, nodes3 = build_tree([1, 2])
    p3, q3 = nodes3[1], nodes3[2]
    result3 = solution.lowestCommonAncestor(root3, p3, q3)
    assert result3.val == 1, f"测试3失败: 期望 1, 得到 {result3.val}"
    print(f"✓ 测试3通过: p=1, q=2, LCA={result3.val}")

    # 测试解法一（哈希表）
    result1_hash = solution.lowestCommonAncestor_hash(root1, p1, q1)
    assert result1_hash.val == 3, f"哈希表解法测试失败"
    print(f"✓ 哈希表解法测试通过")

    print("\n所有测试通过！")


if __name__ == "__main__":
    test()
