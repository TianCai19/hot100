# Repository Guidelines

## Project Structure & Module Organization
- **App**: Next.js pages in `pages/` (`index.js` list view, `pages/problems/[slug].js` detail). Shared UI lives in `components/` (layout, MDX helpers).
- **Content**: Problem write-ups in `content/posts/` using MD/MDX; filenames follow `id-slug.md` (e.g., `160-intersection-of-two-linked-lists.md`).
- **Logic**: MDX parsing helpers in `lib/mdx.js`. Styling is via Tailwind; global styles in `styles/`.
- **Algorithms**: Language reference solutions stored at repo root (e.g., `160_相交链表.py`, `236_二叉树的最近公共祖先.cpp`).
- **Automation**: Custom command docs under `.claude/commands/` for generating new problem files.

## Build, Test, and Development Commands
- `npm install` — install dependencies.
- `npm run dev` — start local dev server at `http://localhost:3000`.
- `npm run build` — production build; use to catch MDX/route errors.
- `npm start` — serve the built site locally.
- Optional sanity checks: run solution files directly (`python3 160_相交链表.py`) or compile C++ (`clang++ -std=c++17 236_二叉树的最近公共祖先.cpp`).

## Coding Style & Naming Conventions
- **JavaScript/React**: 2-space indentation, semicolons, PascalCase components, camelCase helpers. Prefer functional components and hooks.
- **MDX**: Frontmatter should include `title`, `difficulty`, and `description`. Use existing components (`<DifficultyBadge>`, `<Mermaid>`) and fenced code blocks with language tags for highlighting.
- **Tailwind**: Keep utility classes concise; favor composition in shared components over inline repetition.
- **Files**: New content files `id-slug.md`; keep slugs kebab-case. New React components use PascalCase filenames.

## Testing Guidelines
- No dedicated test suite. Rely on `npm run build` to validate MDX compilation and routing, and `npm run dev` for manual page checks.
- For algorithm files, provide minimal runnable examples or asserts; keep input/output visible in scripts when possible.
- Before submitting, verify new links on the index page resolve to the correct slug.

## Commit & Pull Request Guidelines
- Commit style follows existing history: lowercase type prefixes like `feat: ...`, `chore: ...`; initial scaffolding used `Init:`. Scope concisely describes the change (e.g., `feat: add problem 236 - Lowest Common Ancestor of Binary Tree`).
- One logical change per commit. Avoid committing build artifacts or `node_modules`.
- PRs should include: brief summary of changes, screenshots or terminal output for UI/MDX updates, and steps to reproduce any fixed issues. Link related issues when available.

## Content Authoring Tips
- When adding a problem manually, update `pages/index.js` problem list to surface it. Ensure `slug` matches the MDX filename.
- Use consistent section order inside MDX: description → solutions (with language-specific code) → comparison/complexity table.
- Keep wording concise and align code samples between Python and C++ where both are provided.
- For可视化示意（矩阵/网格高亮），MDX已注册组件 `<MaxSquareViz>`（见 `components/MaxSquareViz.js`），直接在文章内使用即可，例如：
  ```mdx
  <MaxSquareViz
    matrix={[
      ['1','0','1'],
      ['1','1','1'],
      ['0','1','1'],
    ]}
    candidate={{ row: 0, col: 0, size: 2 }}  // 可选：红框对比
    square={{ row: 1, col: 1, size: 2 }}     // 必填：绿色框标最大子方块
  />
  ```
  - `row/col` 从 0 开始；`size` 为边长；删除 `candidate` 可去掉红框。无需手动绘图或导入 PNG/SVG 资源。
