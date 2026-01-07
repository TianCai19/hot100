import Link from 'next/link';
import Layout from '../components/Layout';

const problems = [
  { id: 1, title: "两数之和", difficulty: "简单", slug: "1-two-sum" },
  { id: 2, title: "两数相加", difficulty: "中等", slug: "2-add-two-numbers" },
  { id: 3, title: "无重复字符的最长子串", difficulty: "中等", slug: "3-longest-substring-without-repeating-characters" },
  { id: 4, title: "寻找两个正序数组的中位数", difficulty: "困难", slug: "4-median-of-two-sorted-arrays" },
  { id: 5, title: "最长回文子串", difficulty: "中等", slug: "5-longest-palindromic-substring" },
  { id: 10, title: "正则表达式匹配", difficulty: "困难", slug: "10-regular-expression-matching" },
  { id: 11, title: "盛最多水的容器", difficulty: "中等", slug: "11-container-with-most-water" },
  { id: 15, title: "三数之和", difficulty: "中等", slug: "15-3sum" },
  { id: 17, title: "电话号码的字母组合", difficulty: "中等", slug: "17-letter-combinations-of-a-phone-number" },
  { id: 19, title: "删除链表的倒数第 N 个结点", difficulty: "中等", slug: "19-remove-nth-node-from-end-of-list" },
  { id: 20, title: "有效的括号", difficulty: "简单", slug: "20-valid-parentheses" },
  { id: 21, title: "合并两个有序链表", difficulty: "简单", slug: "21-merge-two-sorted-lists" },
  { id: 22, title: "括号生成", difficulty: "中等", slug: "22-generate-parentheses" },
  { id: 23, title: "合并 K 个升序链表", difficulty: "困难", slug: "23-merge-k-sorted-lists" },
  { id: 31, title: "下一个排列", difficulty: "中等", slug: "31-next-permutation" },
  { id: 32, title: "最长有效括号", difficulty: "困难", slug: "32-longest-valid-parentheses" },
  { id: 33, title: "搜索旋转排序数组", difficulty: "中等", slug: "33-search-in-rotated-sorted-array" },
  { id: 34, title: "查找元素的第一个和最后一个位置", difficulty: "中等", slug: "34-find-first-and-last-position" },
  { id: 39, title: "组合总和", difficulty: "中等", slug: "39-combination-sum" },
  { id: 42, title: "接雨水", difficulty: "困难", slug: "42-trapping-rain-water" },
  { id: 46, title: "全排列", difficulty: "中等", slug: "46-permutations" },
  { id: 48, title: "旋转图像", difficulty: "中等", slug: "48-rotate-image" },
  { id: 49, title: "字母异位词分组", difficulty: "中等", slug: "49-group-anagrams" },
  { id: 53, title: "最大子数组和", difficulty: "中等", slug: "53-maximum-subarray" },
  { id: 55, title: "跳跃游戏", difficulty: "中等", slug: "55-jump-game" },
  { id: 56, title: "合并区间", difficulty: "中等", slug: "56-merge-intervals" },
  { id: 62, title: "不同路径", difficulty: "中等", slug: "62-unique-paths" },
  { id: 64, title: "最小路径和", difficulty: "中等", slug: "64-minimum-path-sum" },
  { id: 70, title: "爬楼梯", difficulty: "简单", slug: "70-climbing-stairs" },
  { id: 72, title: "编辑距离", difficulty: "中等", slug: "72-edit-distance" },
  { id: 75, title: "颜色分类", difficulty: "中等", slug: "75-sort-colors" },
  { id: 76, title: "最小覆盖子串", difficulty: "困难", slug: "76-minimum-window-substring" },
  { id: 78, title: "子集", difficulty: "中等", slug: "78-subsets" },
  { id: 79, title: "单词搜索", difficulty: "中等", slug: "79-word-search" },
  { id: 84, title: "柱状图中最大的矩形", difficulty: "困难", slug: "84-largest-rectangle-in-histogram" },
  { id: 85, title: "最大矩形", difficulty: "困难", slug: "85-maximal-rectangle" },
  { id: 94, title: "二叉树的中序遍历", difficulty: "简单", slug: "94-binary-tree-inorder-traversal" },
  { id: 96, title: "不同的二叉搜索树", difficulty: "中等", slug: "96-unique-binary-search-trees" },
  { id: 98, title: "验证二叉搜索树", difficulty: "中等", slug: "98-validate-binary-search-tree" },
  { id: 101, title: "对称二叉树", difficulty: "简单", slug: "101-symmetric-tree" },
  { id: 102, title: "二叉树的层序遍历", difficulty: "中等", slug: "102-binary-tree-level-order-traversal" },
  { id: 104, title: "二叉树的最大深度", difficulty: "简单", slug: "104-maximum-depth-of-binary-tree" },
  { id: 105, title: "从前序与中序遍历序列构造二叉树", difficulty: "中等", slug: "105-construct-binary-tree-from-preorder-and-inorder-traversal" },
  { id: 114, title: "二叉树展开为链表", difficulty: "中等", slug: "114-flatten-binary-tree-to-linked-list" },
  { id: 121, title: "买卖股票的最佳时机", difficulty: "简单", slug: "121-best-time-to-buy-and-sell-stock" },
  { id: 128, title: "最长连续序列", difficulty: "中等", slug: "128-longest-consecutive-sequence" },
  { id: 136, title: "只出现一次的数字", difficulty: "简单", slug: "136-single-number" },
  { id: 139, title: "单词拆分", difficulty: "中等", slug: "139-word-break" },
  { id: 141, title: "环形链表", difficulty: "简单", slug: "141-linked-list-cycle" },
  { id: 160, title: "相交链表", difficulty: "简单", slug: "160-intersection-of-two-linked-lists" },
  { id: 200, title: "岛屿数量", difficulty: "中等", slug: "200-number-of-islands" },
  { id: 206, title: "反转链表", difficulty: "简单", slug: "206-reverse-linked-list" },
  { id: 207, title: "课程表", difficulty: "中等", slug: "207-course-schedule" },
  { id: 208, title: "实现 Trie（前缀树）", difficulty: "中等", slug: "208-implement-trie" },
  { id: 215, title: "数组中的第 K 个最大元素", difficulty: "中等", slug: "215-kth-largest-element" },
  { id: 221, title: "最大正方形", difficulty: "中等", slug: "221-maximal-square" },
  { id: 226, title: "翻转二叉树", difficulty: "简单", slug: "226-invert-binary-tree" },
  { id: 234, title: "回文链表", difficulty: "简单", slug: "234-palindrome-linked-list" },
  { id: 236, title: "二叉树的最近公共祖先", difficulty: "中等", slug: "236-lowest-common-ancestor-of-a-binary-tree" },
  { id: 739, title: "每日温度", difficulty: "中等", slug: "739-daily-temperatures" }
];

const difficultyColors = {
  "简单": "bg-green-600",
  "中等": "bg-yellow-600",
  "困难": "bg-red-600"
};

export default function Home() {
  return (
    <Layout>
      <div className="mb-8">
        <h1 className="text-3xl font-bold text-blue-400 mb-2">LeetCode Hot 100</h1>
        <p className="text-gray-400">算法题解集合 - 精选题目，详解解法</p>
      </div>

      {/* 快速导航 */}
      <div className="mb-8 p-6 bg-gradient-to-br from-blue-900 to-purple-900 rounded-lg">
        <h2 className="text-xl font-semibold text-white mb-4">🚀 快速导航</h2>
        <div className="grid gap-4 md:grid-cols-2">
          <Link
            href="/problems/python-cheatsheet"
            className="block p-4 bg-gray-800 rounded-lg hover:bg-gray-700 transition group border border-blue-500/30"
          >
            <div className="flex items-center justify-between">
              <div>
                <h3 className="text-lg font-semibold text-blue-400 group-hover:text-blue-300">
                  📘 Python 语法速查
                </h3>
                <p className="text-sm text-gray-400 mt-1">
                  LeetCode 常用语法、数据结构、算法模式
                </p>
              </div>
              <svg
                className="w-6 h-6 text-blue-400 group-hover:translate-x-1 transition"
                fill="none"
                stroke="currentColor"
                viewBox="0 0 24 24"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth={2}
                  d="M9 5l7 7-7 7"
                />
              </svg>
            </div>
          </Link>

          <Link
            href="/problems/sql-cheatsheet"
            className="block p-4 bg-gray-800 rounded-lg hover:bg-gray-700 transition group border border-green-500/30"
          >
            <div className="flex items-center justify-between">
              <div>
                <h3 className="text-lg font-semibold text-green-400 group-hover:text-green-300">
                  📊 SQL 语法速查
                </h3>
                <p className="text-sm text-gray-400 mt-1">
                  常用查询语法、窗口函数、LeetCode SQL 题解
                </p>
              </div>
              <svg
                className="w-6 h-6 text-green-400 group-hover:translate-x-1 transition"
                fill="none"
                stroke="currentColor"
                viewBox="0 0 24 24"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth={2}
                  d="M9 5l7 7-7 7"
                />
              </svg>
            </div>
          </Link>
        </div>
      </div>

      <div className="mb-6">
        <h2 className="text-xl font-semibold text-gray-200 mb-4">📝 题目列表</h2>
      </div>

      <div className="grid gap-4 md:grid-cols-2 lg:grid-cols-3">
        {problems.map((problem) => (
          <Link
            key={problem.id}
            href={`/problems/${problem.slug}`}
            className="block p-6 bg-gray-800 rounded-lg hover:bg-gray-700 transition group"
          >
            <div className="flex items-start justify-between mb-3">
              <span className="text-gray-500 text-sm font-mono">{problem.id}</span>
              <span
                className={`px-2 py-1 text-xs rounded text-white ${
                  difficultyColors[problem.difficulty]
                }`}
              >
                {problem.difficulty}
              </span>
            </div>
            <h3 className="text-lg font-semibold text-gray-200 group-hover:text-blue-400 transition">
              {problem.title}
            </h3>
            <div className="mt-4 flex items-center text-sm text-gray-400">
              <span>查看详解</span>
              <svg
                className="w-4 h-4 ml-1 group-hover:translate-x-1 transition"
                fill="none"
                stroke="currentColor"
                viewBox="0 0 24 24"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth={2}
                  d="M9 5l7 7-7 7"
                />
              </svg>
            </div>
          </Link>
        ))}
      </div>

      <div className="mt-12 p-6 bg-gray-800 rounded-lg">
        <h2 className="text-xl font-semibold mb-3">关于本项目</h2>
        <p className="text-gray-300 mb-4">
          本项目整理了 LeetCode Hot 100 中的经典题目，包含详细的解题思路、多种解法对比以及 Python 和 C++ 实现。
        </p>
        <ul className="text-gray-300 space-y-2">
          <li>• 多种解法对比分析</li>
          <li>• Python 和 C++ 双语言实现</li>
          <li>• 详细的复杂度分析</li>
          <li>• 完整的测试用例</li>
        </ul>
      </div>
    </Layout>
  );
}
