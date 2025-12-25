import Link from 'next/link';
import { useRouter } from 'next/router';

export default function Layout({ children }) {
  const router = useRouter();

  return (
    <div className="min-h-screen bg-gray-900 text-gray-100">
      <nav className="bg-gray-800 border-b border-gray-700">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex items-center justify-between h-16">
            <Link href="/" className="text-xl font-bold text-blue-400 hover:text-blue-300">
              LeetCode Hot 100
            </Link>
            <div className="flex items-center gap-6">
              <Link
                href="/"
                className={`hover:text-blue-300 ${router.pathname === '/' ? 'text-blue-400' : 'text-gray-300'}`}
              >
                题目列表
              </Link>
              <a
                href="https://leetcode.cn/problemset/"
                target="_blank"
                rel="noopener noreferrer"
                className="text-gray-400 hover:text-gray-300"
              >
                LeetCode
              </a>
            </div>
          </div>
        </div>
      </nav>

      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {children}
      </main>

      <footer className="bg-gray-800 border-t border-gray-700 mt-16">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-6">
          <p className="text-center text-gray-400">
            © 2025 LeetCode Hot 100 | Built with Next.js & MDX
          </p>
        </div>
      </footer>
    </div>
  );
}
