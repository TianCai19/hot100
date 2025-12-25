import Link from 'next/link';
import { useState } from 'react';

const Mermaid = ({ children }) => {
  const [svg, setSvg] = useState(null);

  if (!svg) {
    // 这里可以集成 mermaid 渲染
    // 为简化，这里直接返回代码块
    return (
      <pre className="mermaid bg-gray-800 p-4 rounded-lg overflow-x-auto">
        <code>{children}</code>
      </pre>
    );
  }

  return <div dangerouslySetInnerHTML={{ __html: svg }} />;
};

const CodeBlock = ({ className, children }) => {
  const language = className?.replace('language-', '') || 'text';

  return (
    <div className="relative group">
      <div className="absolute top-2 right-2 text-xs text-gray-400 opacity-0 group-hover:opacity-100 transition">
        {language}
      </div>
      <pre className={`language-${language} bg-gray-800 p-4 rounded-lg overflow-x-auto`}>
        <code className={className}>{children}</code>
      </pre>
    </div>
  );
};

const Table = ({ children }) => {
  return (
    <div className="overflow-x-auto my-6">
      <table className="min-w-full divide-y divide-gray-700">{children}</table>
    </div>
  );
};

const Th = ({ children }) => {
  return (
    <th className="px-6 py-3 bg-gray-800 text-left text-xs font-medium text-gray-300 uppercase tracking-wider">
      {children}
    </th>
  );
};

const Td = ({ children }) => {
  return (
    <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-300 border-b border-gray-700">
      {children}
    </td>
  );
};

const DifficultyBadge = ({ children }) => {
  const colors = {
    "简单": "bg-green-600",
    "中等": "bg-yellow-600",
    "困难": "bg-red-600"
  };

  const color = colors[children] || "bg-gray-600";

  return (
    <span className={`inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium text-white ${color}`}>
      {children}
    </span>
  );
};

const MDXComponents = {
  h1: (props) => <h1 className="text-3xl font-bold text-blue-400 mb-6" {...props} />,
  h2: (props) => <h2 className="text-2xl font-bold text-gray-200 mt-8 mb-4" {...props} />,
  h3: (props) => <h3 className="text-xl font-semibold text-gray-200 mt-6 mb-3" {...props} />,
  p: (props) => <p className="text-gray-300 leading-relaxed mb-4" {...props} />,
  ul: (props) => <ul className="list-disc list-inside text-gray-300 mb-4 space-y-2" {...props} />,
  ol: (props) => <ol className="list-decimal list-inside text-gray-300 mb-4 space-y-2" {...props} />,
  li: (props) => <li className="ml-4" {...props} />,
  a: (props) => <a className="text-blue-400 hover:text-blue-300 underline" {...props} />,
  code: (props) => (
    <code className="bg-gray-800 px-1.5 py-0.5 rounded text-sm font-mono text-blue-300" {...props} />
  ),
  pre: CodeBlock,
  table: Table,
  th: Th,
  td: Td,
  Mermaid,
  DifficultyBadge,
};

export default MDXComponents;
