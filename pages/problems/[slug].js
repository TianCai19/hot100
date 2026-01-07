import { useRouter } from 'next/router';
import { useEffect, useState } from 'react';
import Layout from '../../components/Layout';
import MDXRenderer, { mdxToSerialised } from '../../lib/mdx';
import TableOfContents from '../../components/TableOfContents';
import fs from 'fs';
import path from 'path';
import matter from 'gray-matter';

export default function ProblemPage({ source, title, difficulty }) {
  const router = useRouter();
  const [headings, setHeadings] = useState([]);

  // 提取标题用于目录
  useEffect(() => {
    const extractHeadings = () => {
      const headingElements = document.querySelectorAll('h2, h3, h4, h5, h6');
      const headingList = Array.from(headingElements).map((element) => {
        const id = element.textContent
          .toLowerCase()
          .replace(/[^\w\s-]/g, '')
          .replace(/\s+/g, '-');

        // 为标题添加ID
        if (!element.id) {
          element.id = id;
        }

        return {
          id: element.id,
          text: element.textContent,
          level: parseInt(element.tagName.charAt(1)) - 1, // h2 -> 1, h3 -> 2, etc.
        };
      });

      setHeadings(headingList);
    };

    // 延迟执行，确保MDX内容已渲染
    const timer = setTimeout(extractHeadings, 100);
    return () => clearTimeout(timer);
  }, [source]);

  // 特殊处理文档类内容，添加目录
  const showTOC = headings.length > 3 && (difficulty === '文档' || title.includes('语法'));

  return (
    <Layout>
      {/* 侧边目录 */}
      {showTOC && <TableOfContents headings={headings} />}

      {/* 主内容区域 */}
      <div className={`transition-all duration-300 ${showTOC ? 'ml-72' : ''}`}>
        <article className="max-w-4xl px-8">
          <div className="mb-6">
            <button
              onClick={() => router.push('/')}
              className="text-blue-400 hover:text-blue-300 flex items-center gap-2 mb-4"
            >
              <svg
                className="w-4 h-4"
                fill="none"
                stroke="currentColor"
                viewBox="0 0 24 24"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth={2}
                  d="M15 19l-7-7 7-7"
                />
              </svg>
              返回题目列表
            </button>
            <h1 className="text-3xl font-bold text-blue-400 mb-2">{title}</h1>
            <div className="flex items-center gap-3">
              <span
                className={`px-3 py-1 text-sm rounded text-white ${
                  difficulty === '简单' ? 'bg-green-600' :
                  difficulty === '中等' ? 'bg-yellow-600' :
                  difficulty === '困难' ? 'bg-red-600' :
                  difficulty === '文档' ? 'bg-purple-600' : 'bg-gray-600'
                }`}
              >
                {difficulty}
              </span>
            </div>
          </div>

          <div className="prose prose-invert prose-lg max-w-none">
            <MDXRenderer source={source} />
          </div>
        </article>
      </div>
    </Layout>
  );
}

export async function getStaticPaths() {
  const problemsDirectory = path.join(process.cwd(), 'content', 'posts');
  const filenames = fs.readdirSync(problemsDirectory);

  const paths = filenames.map((filename) => {
    const slug = filename.replace('.md', '');
    return {
      params: { slug },
    };
  });

  return {
    paths,
    fallback: false,
  };
}

export async function getStaticProps({ params }) {
  const filePath = path.join(process.cwd(), 'content', 'posts', `${params.slug}.md`);
  const fileContents = fs.readFileSync(filePath, 'utf8');
  const { content, data } = matter(fileContents);

  const source = await mdxToSerialised(content);

  return {
    props: {
      source,
      title: data.title || 'Untitled',
      difficulty: data.difficulty || '未知',
    },
  };
}
