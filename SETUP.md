# LeetCode Hot 100 - 项目复现指南

基于 **Next.js 16 + MDX** 的算法题解网站，支持代码高亮和 Mermaid 图表。

## 快速开始

### 1. 克隆项目

```bash
git clone <your-repo-url>
cd hot100
```

### 2. 安装依赖

```bash
npm install
```

### 3. 本地开发

```bash
npm run dev
```

访问 http://localhost:3000

### 4. 构建生产版本

```bash
npm run build
npm start
```

### 5. 部署到 Vercel

```bash
vercel --prod
```

## 项目结构

```
hot100/
├── components/              # React 组件
│   ├── Layout.js           # 页面布局
│   └── MDXComponents.js    # MDX 自定义组件
├── content/
│   └── posts/              # 题目 MDX 文件
├── lib/
│   └── mdx.js              # MDX 渲染工具
├── pages/                  # Next.js 页面
│   ├── index.js            # 首页（题目列表）
│   └── problems/
│       └── [slug].js       # 题目详情页
├── .claude/
│   └── commands/
│       └── add-problem-mdx.md  # 自定义命令
├── content/posts/
│   └── 160-intersection-of-two-linked-lists.md
└── 160_相交链表.py           # Python 代码文件
```

## 添加新题目

使用自定义命令 `/add-problem-mdx`：

```
/add-problem-mdx <粘贴题目内容>
```

### 手动添加步骤

#### 1. 创建 MDX 文件

在 `content/posts/` 目录创建 `{题号}-{题目slug}.md`：

```mdx
---
title: "1. 两数之和"
difficulty: "简单"
description: "给定一个整数数组 nums 和一个整数目标值 target..."
---

# 1. 两数之和

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

...

## 解法一：暴力枚举

### 思路

...

### Python

```python
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        pass
```

### C++

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // ...
    }
};
```

## 解法对比

| 解法 | 时间复杂度 | 空间复杂度 |
|------|-----------|-----------|
| 暴力枚举 | O(n²) | O(1) |
| 哈希表 | O(n) | O(n) |
```

#### 2. 创建代码文件

- `1_两数之和.py` - Python 实现 + 测试
- `1_两数之和.cpp` - C++ 实现 + 测试

#### 3. 更新首页列表

编辑 `pages/index.js`：

```javascript
const problems = [
  { id: 160, title: "相交链表", difficulty: "简单", slug: "160-intersection-of-two-linked-lists" },
  { id: 1, title: "两数之和", difficulty: "简单", slug: "1-two-sum" },  // 新增
];
```

#### 4. 运行测试

```bash
python3 1_两数之和.py
clang++ -std=c++17 -o test 1_两数之和.cpp && ./test && rm test
```

#### 5. 构建验证

```bash
npm run build
```

## MDX 组件

### 可用组件

- `<DifficultyBadge>` - 难度标签（简单/中等/困难）
- `<Mermaid>` - Mermaid 图表

### 示例

```mdx
**难度：<DifficultyBadge>简单</DifficultyBadge>**

<Mermaid>
graph LR
    A --> B
    B --> C
</Mermaid>
```

## 技术栈

- **Next.js 16** - React 框架
- **MDX** - Markdown + React 组件
- **Tailwind CSS** - 样式框架
- **rehype-highlight** - 代码高亮
- **remark-gfm** - GitHub Flavored Markdown
- **gray-matter** - Frontmatter 解析

## 功能特性

✅ SEO 友好（SSG 静态生成）
✅ 响应式设计
✅ 代码语法高亮
✅ Mermaid 图表支持
✅ Frontmatter 元数据
✅ 工业级方案

## 自定义命令

项目包含自定义 Claude 命令：`/add-problem-mdx`

用于快速生成题目的 MDX 文件、代码文件和更新首页列表。

## 许可证

MIT
