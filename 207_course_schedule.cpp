/**
 * 207. 课程表
 * https://leetcode.com/problems/course-schedule/
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 * 解法一：Kahn 算法（拓扑排序 + BFS）
 */
class SolutionKahn {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        /**
         * Kahn 算法 - 基于 BFS 的拓扑排序
         * 时间复杂度: O(V + E)，V = 课程数，E = 边数
         * 空间复杂度: O(V + E)
         */
        // 1. 初始化图和入度数组
        vector<vector<int>> graph(numCourses);
        vector<int> in_degree(numCourses, 0);

        // 2. 构建图
        for (const auto& prereq : prerequisites) {
            int course = prereq[0];
            int pre = prereq[1];
            graph[pre].push_back(course);  // 从先修课程指向依赖课程
            in_degree[course]++;  // 增加依赖课程的入度
        }

        // 3. 初始化队列 - 所有入度为 0 的课程
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> result;
        vector<int> visited(numCourses, 0);

        // 4. BFS 拓扑排序
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            result.push_back(course);
            visited[course] = 1;

            // 遍历所有依赖当前课程的课程
            for (int next_course : graph[course]) {
                if (!visited[next_course]) {
                    in_degree[next_course]--;
                    if (in_degree[next_course] == 0) {
                        q.push(next_course);
                    }
                }
            }
        }

        // 5. 检查是否学完所有课程
        if ((int)result.size() == numCourses) {
            return result;
        }
        return {};
    }
};

/**
 * 解法二：DFS（深度优先搜索）
 */
class SolutionDFS {
private:
    enum State { VISITED, VISITING, DONE };

    bool dfs(int course, const vector<vector<int>>& graph, vector<int>& state, vector<int>& result) {
        if (state[course] == VISITING) {
            // 遇到正在访问的节点，说明存在环
            return true;
        }
        if (state[course] == DONE) {
            // 已经完成，直接返回
            return false;
        }

        // 标记为正在访问
        state[course] = VISITING;

        // 访问所有依赖课程
        for (int next_course : graph[course]) {
            if (dfs(next_course, graph, state, result)) {
                return true;  // 存在环
            }
        }

        // 标记为已完成
        state[course] = DONE;
        // 添加到结果（后序位置）
        result.push_back(course);
        return false;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        /**
         * DFS 算法 - 基于深度优先搜索的拓扑排序
         * 时间复杂度: O(V + E)
         * 空间复杂度: O(V)
         */
        // 1. 构建图
        vector<vector<int>> graph(numCourses);
        for (const auto& prereq : prerequisites) {
            int course = prereq[0];
            int pre = prereq[1];
            graph[pre].push_back(course);
        }

        // 2. 状态数组
        vector<int> state(numCourses, VISITED);
        vector<int> result;

        // 3. 对每个未访问的课程进行 DFS
        for (int i = 0; i < numCourses; i++) {
            if (state[i] == VISITED) {
                if (dfs(i, graph, state, result)) {
                    return {};  // 存在环，无法完成所有课程
                }
            }
        }

        // 4. 反转结果得到正确的拓扑序
        reverse(result.begin(), result.end());
        return result;
    }
};

bool isValidOrder(int numCourses, const vector<vector<int>>& prerequisites, const vector<int>& order) {
    /**
     * 验证生成的课程顺序是否有效
     */
    if ((int)order.size() != numCourses) {
        return false;
    }

    // 检查是否包含所有课程
    unordered_map<int, int> pos;
    for (int i = 0; i < numCourses; i++) {
        pos[order[i]] = i;
    }

    for (int course = 0; course < numCourses; course++) {
        if (pos.find(course) == pos.end()) {
            return false;
        }
    }

    // 检查先修关系
    unordered_map<int, vector<int>> prereq_map;
    for (const auto& prereq : prerequisites) {
        int course = prereq[0];
        int pre = prereq[1];
        prereq_map[course].push_back(pre);
    }

    for (const auto& [course, prereqs] : prereq_map) {
        int course_pos = pos[course];
        for (int pre : prereqs) {
            if (pos[pre] >= course_pos) {
                return false;
            }
        }
    }

    return true;
}

struct TestCase {
    int numCourses;
    vector<vector<int>> prerequisites;
    bool expectedValid;
    string description;
};

void testSolution(const string& name, SolutionKahn* solution) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "测试方法: " << name << "\n";
    cout << string(60, '=') << "\n";

    vector<TestCase> test_cases = {
        {2, {{1, 0}}, true, "示例1：简单依赖关系"},
        {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true, "示例2：复杂依赖关系"},
        {1, {}, true, "示例3：无需先修课程"},
        {2, {{0, 1}, {1, 0}}, false, "循环依赖1"},
        {3, {{1, 0}, {2, 1}, {0, 2}}, false, "循环依赖2"},
        {3, {{1, 0}, {2, 1}}, true, "链式依赖"},
        {5, {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 2}}, true, "多依赖关系"},
        {4, {{0, 1}, {1, 2}, {2, 3}}, true, "单链依赖"},
        {3, {}, true, "无先修要求"},
        {6, {{1, 0}, {2, 1}, {3, 2}, {4, 1}, {5, 3}, {5, 4}}, true, "复杂网状依赖"}
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < test_cases.size(); i++) {
        const auto& test = test_cases[i];
        try {
            vector<int> result = solution->findOrder(test.numCourses, const_cast<vector<vector<int>>&>(test.prerequisites));
            bool isValid = isValidOrder(test.numCourses, test.prerequisites, result);

            if (isValid == test.expectedValid) {
                if (test.expectedValid) {
                    cout << "✓ 测试 " << (i + 1) << " 通过: " << test.description << "\n";
                    cout << "  课程数: " << test.numCourses << ", 先修: ";
                    for (const auto& prereq : test.prerequisites) {
                        cout << "[" << prereq[0] << "," << prereq[1] << "]";
                    }
                    cout << "\n";
                    cout << "  学习顺序: [";
                    for (size_t j = 0; j < result.size(); j++) {
                        cout << result[j];
                        if (j < result.size() - 1) cout << ", ";
                    }
                    cout << "]\n";
                } else {
                    cout << "✓ 测试 " << (i + 1) << " 通过: " << test.description << "\n";
                    cout << "  正确检测到循环依赖，返回空数组\n";
                }
                passed++;
            } else {
                cout << "✗ 测试 " << (i + 1) << " 失败: " << test.description << "\n";
                cout << "  课程数: " << test.numCourses << ", 先修: ";
                for (const auto& prereq : test.prerequisites) {
                    cout << "[" << prereq[0] << "," << prereq[1] << "]";
                }
                cout << "\n";
                cout << "  结果: [";
                for (size_t j = 0; j < result.size(); j++) {
                    cout << result[j];
                    if (j < result.size() - 1) cout << ", ";
                }
                cout << "], 期望有效性: " << (test.expectedValid ? "true" : "false") << "\n";
                failed++;
            }
        } catch (const exception& e) {
            cout << "✗ 测试 " << (i + 1) << " 出现异常: " << test.description << "\n";
            cout << "  异常: " << e.what() << "\n";
            failed++;
        }
    }

    cout << string(60, '-') << "\n";
    cout << "测试结果: " << passed << " 通过, " << failed << " 失败\n";
    cout << string(60, '-') << "\n";

    if (failed == 0) {
        cout << "✓ " << name << " 所有测试通过!\n";
    }
}

void testSolutionDFS(const string& name, SolutionDFS* solution) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "测试方法: " << name << "\n";
    cout << string(60, '=') << "\n";

    vector<TestCase> test_cases = {
        {2, {{1, 0}}, true, "示例1：简单依赖关系"},
        {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true, "示例2：复杂依赖关系"},
        {1, {}, true, "示例3：无需先修课程"},
        {2, {{0, 1}, {1, 0}}, false, "循环依赖1"},
        {3, {{1, 0}, {2, 1}, {0, 2}}, false, "循环依赖2"},
        {3, {{1, 0}, {2, 1}}, true, "链式依赖"},
        {5, {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 2}}, true, "多依赖关系"},
        {4, {{0, 1}, {1, 2}, {2, 3}}, true, "单链依赖"},
        {3, {}, true, "无先修要求"},
        {6, {{1, 0}, {2, 1}, {3, 2}, {4, 1}, {5, 3}, {5, 4}}, true, "复杂网状依赖"}
    };

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < test_cases.size(); i++) {
        const auto& test = test_cases[i];
        try {
            vector<int> result = solution->findOrder(test.numCourses, const_cast<vector<vector<int>>&>(test.prerequisites));
            bool isValid = isValidOrder(test.numCourses, test.prerequisites, result);

            if (isValid == test.expectedValid) {
                if (test.expectedValid) {
                    cout << "✓ 测试 " << (i + 1) << " 通过: " << test.description << "\n";
                    cout << "  课程数: " << test.numCourses << ", 先修: ";
                    for (const auto& prereq : test.prerequisites) {
                        cout << "[" << prereq[0] << "," << prereq[1] << "]";
                    }
                    cout << "\n";
                    cout << "  学习顺序: [";
                    for (size_t j = 0; j < result.size(); j++) {
                        cout << result[j];
                        if (j < result.size() - 1) cout << ", ";
                    }
                    cout << "]\n";
                } else {
                    cout << "✓ 测试 " << (i + 1) << " 通过: " << test.description << "\n";
                    cout << "  正确检测到循环依赖，返回空数组\n";
                }
                passed++;
            } else {
                cout << "✗ 测试 " << (i + 1) << " 失败: " << test.description << "\n";
                cout << "  课程数: " << test.numCourses << ", 先修: ";
                for (const auto& prereq : test.prerequisites) {
                    cout << "[" << prereq[0] << "," << prereq[1] << "]";
                }
                cout << "\n";
                cout << "  结果: [";
                for (size_t j = 0; j < result.size(); j++) {
                    cout << result[j];
                    if (j < result.size() - 1) cout << ", ";
                }
                cout << "], 期望有效性: " << (test.expectedValid ? "true" : "false") << "\n";
                failed++;
            }
        } catch (const exception& e) {
            cout << "✗ 测试 " << (i + 1) << " 出现异常: " << test.description << "\n";
            cout << "  异常: " << e.what() << "\n";
            failed++;
        }
    }

    cout << string(60, '-') << "\n";
    cout << "测试结果: " << passed << " 通过, " << failed << " 失败\n";
    cout << string(60, '-') << "\n";

    if (failed == 0) {
        cout << "✓ " << name << " 所有测试通过!\n";
    }
}

int main() {
    cout << "=" << string(60, '=') << "\n";
    cout << "测试课程表问题\n";
    cout << string(60, '=') << "\n";

    // 测试 Kahn 算法
    SolutionKahn solution_kahn;
    testSolution("Kahn 算法 (BFS)", &solution_kahn);

    // 测试 DFS
    SolutionDFS solution_dfs;
    testSolutionDFS("DFS", &solution_dfs);

    cout << "\n" << string(60, '=') << "\n";
    cout << "所有测试完成!\n";
    cout << string(60, '=') << "\n";

    return 0;
}
