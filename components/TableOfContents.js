import { useState, useEffect } from 'react';

export default function TableOfContents({ headings = [] }) {
  const [activeId, setActiveId] = useState('');

  useEffect(() => {
    const observerOptions = {
      rootMargin: '-100px 0px -66%',
      threshold: 1,
    };

    const observerCallback = (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          setActiveId(entry.target.id);
        }
      });
    };

    const observer = new IntersectionObserver(observerCallback, observerOptions);

    // 观察所有标题元素
    headings.forEach((heading) => {
      const element = document.getElementById(heading.id);
      if (element) {
        observer.observe(element);
      }
    });

    return () => observer.disconnect();
  }, [headings]);

  const scrollToHeading = (id) => {
    const element = document.getElementById(id);
    if (element) {
      const offset = 100; // 偏移量，避免被固定导航栏遮挡
      const elementPosition = element.offsetTop - offset;
      window.scrollTo({
        top: elementPosition,
        behavior: 'smooth',
      });
    }
  };

  if (headings.length === 0) {
    return null;
  }

  return (
    <div className="fixed left-0 top-24 h-full w-64 bg-gray-900/95 backdrop-blur-sm border-r border-gray-700 overflow-y-auto p-6 z-40">
      <h3 className="text-lg font-semibold text-gray-200 mb-4 sticky top-0 bg-gray-900/95 pb-2">
        📋 目录
      </h3>
      <nav>
        <ul className="space-y-2">
          {headings.map((heading) => (
            <li key={heading.id}>
              <button
                onClick={() => scrollToHeading(heading.id)}
                className={`w-full text-left px-3 py-2 rounded-lg transition-all text-sm ${
                  activeId === heading.id
                    ? 'bg-blue-600 text-white shadow-lg'
                    : 'text-gray-400 hover:text-gray-200 hover:bg-gray-800'
                }`}
                style={{
                  paddingLeft: `${Math.min(heading.level * 12, 36)}px`,
                }}
              >
                <span className="truncate block">{heading.text}</span>
              </button>
            </li>
          ))}
        </ul>
      </nav>
    </div>
  );
}
