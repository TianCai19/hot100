"""
207. 课程表
https://leetcode.com/problems/course-schedule/
"""

from typing import List
from collections import deque, defaultdict


class SolutionKahn:
    """解法一：Kahn 算法（拓扑排序 + BFS）"""
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        """
        Kahn 算法 - 基于 BFS 的拓扑排序
        时间复杂度: O(V + E)，V = 课程数，E = 边数
        空间复杂度: O(V + E)
        """
        # 1. 初始化图和入度数组
        graph = defaultdict(list)  # graph[u] = [v1, v2, ...]
        in_degree = [0] * numCourses

        # 2. 构建图
        for course, prereq in prerequisites:
            graph[prereq].append(course)  # 从先修课程指向依赖课程
            in_degree[course] += 1  # 增加依赖课程的入度

        # 3. 初始化队列 - 所有入度为 0 的课程
        queue = deque([i for i in range(numCourses) if in_degree[i] == 0])
        result = []

        # 4. BFS 拓扑排序
        while queue:
            course = queue.popleft()
            result.append(course)

            # 遍历所有依赖当前课程的课程
            for next_course in graph[course]:
                in_degree[next_course] -= 1
                if in_degree[next_course] == 0:
                    queue.append(next_course)

        # 5. 检查是否学完所有课程
        return result if len(result) == numCourses else []


class SolutionDFS:
    """解法二：DFS（深度优先搜索）"""
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        """
        DFS 算法 - 基于深度优先搜索的拓扑排序
        时间复杂度: O(V + E)
        空间复杂度: O(V)
        """
        # 1. 构建图
        graph = [[] for _ in range(numCourses)]
        for course, prereq in prerequisites:
            graph[prereq].append(course)

        # 2. 状态数组
        VISITED = 0
        VISITING = 1
        DONE = 2
        state = [VISITED] * numCourses
        result = []
        has_cycle = False

        # 3. DFS 递归函数
        def dfs(course: int):
            nonlocal has_cycle
            if state[course] == VISITING:
                # 遇到正在访问的节点，说明存在环
                has_cycle = True
                return
            if state[course] == DONE or has_cycle:
                # 已经完成或有环，直接返回
                return

            # 标记为正在访问
            state[course] = VISITING

            # 访问所有依赖课程
            for next_course in graph[course]:
                dfs(next_course)
                if has_cycle:
                    return

            # 标记为已完成
            state[course] = DONE
            # 添加到结果（后序位置）
            result.append(course)

        # 4. 对每个未访问的课程进行 DFS
        for i in range(numCourses):
            if state[i] == VISITED:
                dfs(i)
                if has_cycle:
                    return []

        # 5. 反转结果得到正确的拓扑序
        return result[::-1]


def is_valid_order(numCourses: int, prerequisites: List[List[int]], order: List[int]) -> bool:
    """
    验证生成的课程顺序是否有效
    """
    if len(order) != numCourses:
        return False

    # 检查是否包含所有课程
    if set(order) != set(range(numCourses)):
        return False

    # 检查先修关系
    prereq_map = {}
    for course, prereq in prerequisites:
        if course not in prereq_map:
            prereq_map[course] = []
        prereq_map[course].append(prereq)

    for course in order:
        if course in prereq_map:
            for prereq in prereq_map[course]:
                if prereq not in order[:order.index(course)]:
                    return False

    return True


def test_solution():
    """测试所有解法"""
    print("=" * 60)
    print("测试课程表问题")
    print("=" * 60)

    test_cases = [
        {
            "numCourses": 2,
            "prerequisites": [[1, 0]],
            "expected_valid": True,
            "description": "示例1：简单依赖关系"
        },
        {
            "numCourses": 4,
            "prerequisites": [[1, 0], [2, 0], [3, 1], [3, 2]],
            "expected_valid": True,
            "description": "示例2：复杂依赖关系"
        },
        {
            "numCourses": 1,
            "prerequisites": [],
            "expected_valid": True,
            "description": "示例3：无需先修课程"
        },
        {
            "numCourses": 2,
            "prerequisites": [[0, 1], [1, 0]],
            "expected_valid": False,
            "description": "循环依赖1"
        },
        {
            "numCourses": 3,
            "prerequisites": [[1, 0], [2, 1], [0, 2]],
            "expected_valid": False,
            "description": "循环依赖2"
        },
        {
            "numCourses": 3,
            "prerequisites": [[1, 0], [2, 1]],
            "expected_valid": True,
            "description": "链式依赖"
        },
        {
            "numCourses": 5,
            "prerequisites": [[1, 0], [2, 0], [3, 1], [3, 2], [4, 2]],
            "expected_valid": True,
            "description": "多依赖关系"
        },
        {
            "numCourses": 4,
            "prerequisites": [[0, 1], [1, 2], [2, 3]],
            "expected_valid": True,
            "description": "单链依赖"
        },
        {
            "numCourses": 3,
            "prerequisites": [],
            "expected_valid": True,
            "description": "无先修要求"
        },
        {
            "numCourses": 6,
            "prerequisites": [[1, 0], [2, 1], [3, 2], [4, 1], [5, 3], [5, 4]],
            "expected_valid": True,
            "description": "复杂网状依赖"
        }
    ]

    methods = [
        ("Kahn 算法 (BFS)", SolutionKahn()),
        ("DFS", SolutionDFS())
    ]

    for method_name, solution in methods:
        print(f"\n{'=' * 60}")
        print(f"测试方法: {method_name}")
        print(f"{'=' * 60}")

        passed = 0
        failed = 0

        for i, test_case in enumerate(test_cases, 1):
            numCourses = test_case["numCourses"]
            prerequisites = test_case["prerequisites"]
            expected_valid = test_case["expected_valid"]
            description = test_case["description"]

            try:
                result = solution.findOrder(numCourses, prerequisites)
                is_valid = is_valid_order(numCourses, prerequisites, result)

                if is_valid == expected_valid:
                    if expected_valid:
                        print(f"✓ 测试 {i} 通过: {description}")
                        print(f"  课程数: {numCourses}, 先修: {prerequisites}")
                        print(f"  学习顺序: {result}")
                    else:
                        print(f"✓ 测试 {i} 通过: {description}")
                        print(f"  正确检测到循环依赖，返回空数组")
                    passed += 1
                else:
                    print(f"✗ 测试 {i} 失败: {description}")
                    print(f"  课程数: {numCourses}, 先修: {prerequisites}")
                    print(f"  结果: {result}, 期望有效性: {expected_valid}")
                    failed += 1
            except Exception as e:
                print(f"✗ 测试 {i} 出现异常: {description}")
                print(f"  异常: {e}")
                failed += 1

        print(f"\n{'-' * 60}")
        print(f"测试结果: {passed} 通过, {failed} 失败")
        print(f"{'-' * 60}")

        if failed == 0:
            print(f"✓ {method_name} 所有测试通过!")

    print(f"\n{'=' * 60}")
    print("所有测试完成!")
    print(f"{'=' * 60}")


def test_performance():
    """性能测试"""
    print("\n" + "=" * 60)
    print("性能测试")
    print("=" * 60)

    import time

    # 生成大量测试数据
    import random
    random.seed(42)

    numCourses = 1000
    numPrerequisites = 2000

    prerequisites = []
    for _ in range(numPrerequisites):
        course = random.randint(0, numCourses - 1)
        prereq = random.randint(0, numCourses - 1)
        if course != prereq:
            prerequisites.append([course, prereq])

    for name, solution in [("Kahn 算法 (BFS)", SolutionKahn()), ("DFS", SolutionDFS())]:
        print(f"\n测试 {name}:")
        start_time = time.time()
        result = solution.findOrder(numCourses, prerequisites)
        elapsed_time = time.time() - start_time

        print(f"  课程数: {numCourses}")
        print(f"  先修关系数: {len(prerequisites)}")
        print(f"  执行时间: {elapsed_time:.4f} 秒")
        print(f"  能否完成所有课程: {'是' if result else '否'}")


if __name__ == "__main__":
    test_solution()
    test_performance()
