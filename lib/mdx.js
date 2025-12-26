import { MDXRemote } from 'next-mdx-remote';
import { serialize } from 'next-mdx-remote/serialize';
import remarkGfm from 'remark-gfm';
import rehypeHighlight from 'rehype-highlight';
import MDXComponents from '../components/MDXComponents';

export async function mdxToSerialised(mdx) {
  return await serialize(mdx, {
    mdxOptions: {
      remarkPlugins: [remarkGfm],
      rehypePlugins: [rehypeHighlight],
    },
  });
}

export default function MDXRenderer({ source }) {
  return <MDXRemote {...source} components={MDXComponents} />;
}
