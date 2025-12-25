# LeetCode Hot 100

基于 **Next.js + MDX** 的算法题解网站，支持 Markdown 渲染、代码高亮和 Mermaid 图表。

## 技术栈

- **Next.js 16** - React 框架
- **MDX** - Markdown + React 组件
- **Tailwind CSS** - 样式框架
- **rehype-highlight** - 代码高亮
- **remark-gfm** - GitHub Flavored Markdown
- **gray-matter** - Frontmatter 解析

## 项目结构

```
hot100-new/
├── components/          # React 组件
│   ├── Layout.js       # 布局组件
│   └── MDXComponents.js # MDX 自定义组件
├── content/
│   └── posts/          # 题目 MDX 文件
├── lib/
│   └── mdx.js          # MDX 渲染工具
├── pages/              # Next.js 页面
│   ├── index.js        # 首页
│   └── problems/
│       └── [slug].js   # 题目详情页
└── content/posts/
    └── 160-intersection-of-two-linked-lists.md
```

## 添加新题目

### 1. 创建 MDX 文件

在 `content/posts/` 目录下创建 `{题号}-{题目slug}.md` 文件：

```mdx
---
title: "160. 相交链表"
difficulty: "简单"
description: "题目描述..."
---

# 160. 相交链表

## 题目描述

...

## 解法一：哈希集合

### 思路

...

### Python

```python
class Solution:
    def method(self):
        pass
```

### C++

```cpp
class Solution {
public:
    void method() {}
};
```
```

### 2. 更新首页列表

编辑 `pages/index.js`，在 `problems` 数组中添加新题目：

```javascript
const problems = [
  { id: 160, title: "相交链表", difficulty: "简单", slug: "160-intersection-of-two-linked-lists" },
  { id: 1, title: "两数之和", difficulty: "简单", slug: "1-two-sum" },  // 新增
];
```

## 本地开发

```bash
npm install
npm run dev
```

访问 http://localhost:3000

## 部署到 Vercel

```bash
npm run build
vercel --prod
```

或直接 push 到 GitHub，Vercel 会自动检测并部署。

## MDX 自定义组件

- `<DifficultyBadge>` - 难度标签
- `<Mermaid>` - Mermaid 图表
- 代码块自动语法高亮

## 特性

✅ SEO 友好
✅ 响应式设计
✅ 代码语法高亮
✅ Mermaid 图表支持
✅ Frontmatter 元数据
✅ 静态生成（SSG）
✅ 工业级方案

## 许可证

MIT
