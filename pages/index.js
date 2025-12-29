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
