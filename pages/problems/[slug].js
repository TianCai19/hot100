import { useRouter } from 'next/router';
import Layout from '../../components/Layout';
import MDXRenderer, { mdxToSerialised } from '../../lib/mdx';
import fs from 'fs';
import path from 'path';
import matter from 'gray-matter';

export default function ProblemPage({ source, title, difficulty }) {
  const router = useRouter();

  return (
    <Layout>
      <article className="max-w-4xl">
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
                difficulty === '中等' ? 'bg-yellow-600' : 'bg-red-600'
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
