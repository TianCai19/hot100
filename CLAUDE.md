# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **LeetCode Hot 100** solutions website built with **Next.js 16 + MDX**. The site displays algorithm problem solutions with explanations, code examples (Python & C++), and complexity analysis.

**Live Site:** https://hot100-c6yw7v9ok-tiancai19s-projects.vercel.app

## Architecture

### Content System

The site uses **MDX** (Markdown + React components) to render problem solutions:

- **MDX Files:** `content/posts/{problem-slug}.md`
- **Static Generation:** `pages/problems/[slug].js` uses `getStaticProps` to read and serialize MDX at build time
- **Frontmatter:** Each MDX file has YAML frontmatter with `title`, `difficulty`, and `description`

### Custom MDX Components

Available custom components in `components/MDXComponents.js`:

- `<DifficultyBadge>` - Renders difficulty badge (简单/中等/困难) with color coding
- `<Mermaid>` - Container for Mermaid diagrams (currently renders as code block)
- `<MaxSquareViz>` - Grid/SVG visualizer for矩阵类题，位于 `components/MaxSquareViz.js`
- Code blocks automatically get syntax highlighting via `rehype-highlight`

### Data Flow

1. **Home Page** (`pages/index.js`): Hardcoded `problems` array with metadata (id, title, difficulty, slug)
2. **Problem Page** (`pages/problems/[slug].js`):
   - Reads MDX file from `content/posts/`
   - Uses `gray-matter` to parse frontmatter
   - Serializes MDX with `next-mdx-remote`
   - Renders via `MDXRenderer` component

### File Organization

```
hot100/
├── content/posts/              # MDX files for problems
├── pages/                      # Next.js pages
│   ├── index.js               # Problem list
│   └── problems/[slug].js     # Individual problem page
├── components/                 # React components
│   ├── Layout.js              # Page layout wrapper
│   └── MDXComponents.js       # Custom MDX components
├── lib/mdx.js                 # MDX rendering utilities
├── {problem}.py               # Python implementations + tests
├── {problem}.cpp              # C++ implementations + tests
└── .claude/commands/          # Custom Claude commands
```

## Common Development Commands

### Setup

```bash
npm install
```

### Development

```bash
npm run dev
# Opens http://localhost:3000
```

### Building & Testing

```bash
# Build production static site
npm run build

# Start production server
npm start

# Run Python tests (for specific problem)
python3 {problem}.py

# Run C++ tests (for specific problem)
clang++ -std=c++17 -o test {problem}.cpp && ./test && rm test
```

### Deployment

```bash
# Deploy to Vercel (production)
vercel --prod
```

## Adding New Problems

Use the custom command: `/add-problem-mdx <problem-content>`

Or manually:

1. **Create MDX file:** `content/posts/{id}-{slug}.md`
   - Include frontmatter: `title`, `difficulty`, `description`
   - Use `<DifficultyBadge>` for difficulty display
   - Use `<Mermaid>` for diagrams
   - For矩阵/网格示意图，直接用已注册的 `<MaxSquareViz>` 生成 SVG，无需手绘或外部图片。例如：
     ```mdx
     <MaxSquareViz
       matrix={[
         ['1','0','1','0'],
         ['1','1','1','1'],
         ['0','1','1','1'],
       ]}
       candidate={{ row: 0, col: 1, size: 2 }}  // 可选红框
       square={{ row: 1, col: 1, size: 2 }}     // 绿色框（必填）
     />
     ```
     `row/col` 从 0 起，`size` 为边长；删除 `candidate` 可隐藏红框。
   - Include both Python and C++ code blocks with syntax highlighting
   - **IMPORTANT:** Provide **multiple solutions** when applicable:
     - At least 2 different approaches (e.g., brute force + optimal)
     - Common pattern: 暴力解 → 哈希表/双指针 → 动态规划/贪心
     - Label clearly (e.g., "解法一：哈希集合", "解法二：双指针（推荐）")
     - Include complexity comparison table when solutions differ significantly

2. **Create code files:**
   - `{id}_{problem-name}.py` - Python implementation with tests
   - `{id}_{problem-name}.cpp` - C++ implementation with tests

3. **Update homepage:** Edit `pages/index.js`, add to `problems` array:
   ```javascript
   { id: 1, title: "Two Sum", difficulty: "简单", slug: "1-two-sum" }
   ```

4. **Run tests:**
   ```bash
   python3 {problem}.py
   clang++ -std=c++17 -o test {problem}.cpp && ./test && rm test
   npm run build
   ```

5. **🔍 Verify New Problems (IMPORTANT):**
   After adding a new problem, use **Chrome DevTools MCP** to verify:
   ```bash
   # Navigate to the new problem page
   navigate_page -> http://localhost:3000/problems/{slug}

   # Check for console errors
   list_console_messages

   # Verify Mermaid diagrams render correctly
   # Check SVG components display properly
   # Ensure syntax highlighting works
   ```

   **⚠️ Common Issues to Check:**
   - Mermaid reserved keywords: `not`, `has`, `and`, `or` → use alternatives
   - HTML tags like `<br/>` → replace with spaces or line breaks
   - Chinese characters in Mermaid → use English for diagram labels
   - SVG rendering errors → verify component registration

   **Reference:** https://github.com/ChromeDevTools/chrome-devtools-mcp

## Key Dependencies

- **next@16** - React framework with SSG
- **next-mdx-remote@5** - MDX rendering for Next.js
- **remark-gfm** - GitHub Flavored Markdown
- **rehype-highlight** - Code syntax highlighting
- **gray-matter** - Frontmatter parsing
- **Tailwind CSS** - Styling (loaded via CDN in Layout)

## Technical Notes

- **SSG Pattern:** All pages are statically generated at build time via `getStaticProps`
- **No Database:** Content is pure MDX files + frontmatter
- **No API Routes:** All data comes from filesystem at build time
- **Code Files:** Stored in root, not part of MDX (allows running tests independently)

## Code Style

- **Python:** Type hints required, concise implementation
- **C++:** C++17 standard, includes necessary headers
- **MDX:** Use custom components, include complexity analysis tables
- **Tests:** Must cover all examples from problem statement
