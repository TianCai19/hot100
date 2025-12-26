# LeetCode Hot 100

基于 **Next.js 16 + MDX** 的算法题解网站，支持代码高亮和 Mermaid 图表。

在线预览：https://hot100-c6yw7v9ok-tiancai19s-projects.vercel.app

## 快速开始

### 克隆项目

```bash
git clone <your-repo-url>
cd hot100
npm install
npm run dev
```

访问 http://localhost:3000

### 部署

```bash
npm run build
vercel --prod
```

## 项目特性

✅ Next.js 16 + MDX
✅ 静态生成（SSG）
✅ 代码语法高亮
✅ Mermaid 图表
✅ 响应式设计
✅ 两种解法对比（Python + C++）

## 技术栈

- **Next.js 16** - React 框架
- **MDX** - Markdown + React 组件
- **Tailwind CSS** - 样式框架
- **rehype-highlight** - 代码高亮
- **remark-gfm** - GitHub Flavored Markdown

## 添加新题目

使用自定义命令：`/add-problem-mdx <题目内容>`

或参考 [SETUP.md](./SETUP.md) 了解详细步骤。

## 项目结构

```
hot100/
├── components/          # React 组件
├── content/posts/       # 题目 MDX 文件
├── lib/mdx.js          # MDX 渲染工具
├── pages/              # Next.js 页面
└── .claude/commands/   # 自定义命令
```

## 许可证

MIT
