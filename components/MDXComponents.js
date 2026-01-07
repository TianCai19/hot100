import { Children, useEffect, useRef, useState } from 'react';
import MaxSquareViz from './MaxSquareViz';

const collectText = (node) => {
  if (typeof node === 'string') {
    return node;
  }

  if (Array.isArray(node)) {
    return node.map(collectText).join('');
  }

  if (node && node.props && node.props.children) {
    return collectText(node.props.children);
  }

  return '';
};

const normalizeMermaidContent = (content) => collectText(Children.toArray(content)).trim();

const Mermaid = ({ children }) => {
  const containerRef = useRef(null);
  const [svg, setSvg] = useState(null);
  const [hasError, setHasError] = useState(false);

  useEffect(() => {
    let cancelled = false;

    const renderMermaid = async () => {
      setHasError(false);
      setSvg(null);

      try {
        const mermaid = (await import('mermaid')).default;
        mermaid.initialize({
          startOnLoad: false,
          theme: 'dark',
          securityLevel: 'loose',
        });

        const id = `mermaid-${Math.random().toString(36).slice(2, 9)}`;
        const graphDefinition = normalizeMermaidContent(children);

        if (!graphDefinition) {
          console.warn('Mermaid: empty graph definition', children);
          setHasError(true);
          return;
        }

        const { svg } = await mermaid.render(id, graphDefinition);
        if (!cancelled) {
          setSvg(svg);
        }
      } catch (error) {
        if (!cancelled) {
          console.error('Mermaid render error:', error);
          setHasError(true);
        }
      }
    };

    renderMermaid();

    return () => {
      cancelled = true;
    };
  }, [children]);

  if (hasError) {
    return (
      <pre className="mermaid bg-gray-800 p-4 rounded-lg overflow-x-auto">
        <code>{children}</code>
      </pre>
    );
  }

  if (svg) {
    return <div className="mermaid my-4 flex justify-center" dangerouslySetInnerHTML={{ __html: svg }} />;
  }

  return <div className="mermaid my-4 text-gray-400">加载图表中...</div>;
};

const CodeBlock = ({ className, children }) => {
  const language = className?.replace('language-', '') || 'text';
  const [copied, setCopied] = useState(false);

  const handleCopy = async () => {
    // Try to extract code text from the actual DOM element
    const codeElement = document.querySelector(`code.${className}`);
    let codeText = '';

    if (codeElement) {
      // Get the text content from the DOM
      codeText = codeElement.textContent || codeElement.innerText || '';
    } else if (typeof children === 'string') {
      // Fallback to children prop
      codeText = children;
    }

    try {
      // Try modern clipboard API first
      if (navigator.clipboard && window.isSecureContext) {
        await navigator.clipboard.writeText(codeText);
      } else {
        // Fallback to legacy method
        const textArea = document.createElement('textarea');
        textArea.value = codeText;
        textArea.style.position = 'fixed';
        textArea.style.left = '-999999px';
        textArea.style.top = '-999999px';
        document.body.appendChild(textArea);
        textArea.focus();
        textArea.select();
        const successful = document.execCommand('copy');
        document.body.removeChild(textArea);
        if (!successful) {
          throw new Error('execCommand failed');
        }
      }
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
      console.log('Code copied successfully:', codeText.substring(0, 50) + '...');
    } catch (error) {
      console.error('Failed to copy code:', error);
      // Fallback: select the code text so user can manually copy
      if (codeElement) {
        const range = document.createRange();
        range.selectNodeContents(codeElement);
        const selection = window.getSelection();
        selection.removeAllRanges();
        selection.addRange(range);
      }
    }
  };

  return (
    <div className="relative group">
      <div className="absolute top-2 right-2 flex items-center gap-2 opacity-0 group-hover:opacity-100 transition-opacity">
        <span className="text-xs text-gray-400">
          {language}
        </span>
        <button
          onClick={handleCopy}
          className="flex items-center gap-1 px-2 py-1 bg-gray-700 hover:bg-gray-600 rounded text-xs text-gray-300 transition-colors"
          title="复制代码"
        >
          {copied ? (
            <>
              <svg className="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M5 13l4 4L19 7" />
              </svg>
              已复制
            </>
          ) : (
            <>
              <svg className="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M8 16H6a2 2 0 01-2-2V6a2 2 0 012-2h8a2 2 0 012 2v2m-6 12h8a2 2 0 002-2v-8a2 2 0 00-2-2h-8a2 2 0 00-2 2v8a2 2 0 002 2z" />
              </svg>
              复制
            </>
          )}
        </button>
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
  MaxSquareViz,
};

export default MDXComponents;
