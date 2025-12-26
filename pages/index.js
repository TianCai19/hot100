import Link from 'next/link';
import Layout from '../components/Layout';

const problems = [
  { id: 160, title: "相交链表", difficulty: "简单", slug: "160-intersection-of-two-linked-lists" },
  { id: 236, title: "二叉树的最近公共祖先", difficulty: "中等", slug: "236-lowest-common-ancestor-of-a-binary-tree" }
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
