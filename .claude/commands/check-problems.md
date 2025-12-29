# 检查题目页面命令

## 使用 Chrome DevTools MCP 检查新增题目

在添加新题目后，使用以下步骤验证页面是否正常显示：

### 1. 启动 Chrome DevTools MCP
确保浏览器已打开且页面已加载

### 2. 导航到每个题目页面
依次访问所有题目页面：
- 检查页面是否正常加载
- 查看控制台是否有错误

### 3. 重点检查项
- ✅ **Mermaid 图表**：确保无渲染错误
- ✅ **SVG 图表**：确保正确显示
- ✅ **代码块**：确保语法高亮正常
- ✅ **控制台**：确保无 JavaScript 错误

### 4. 常见问题
- Mermaid 保留字：`not`、`has`、`and` 等
- HTML 标签：如 `<br/>` 应替换为空格或换行
- 中文字符：在 Mermaid 中可能导致解析错误

### 5. 修复后验证
- 刷新页面确保缓存更新
- 再次检查控制台确认无错误

---

**参考 MCP：** https://github.com/ChromeDevTools/chrome-devtools-mcp

**示例命令：**
```bash
# 导航到题目页面
navigate_page -> http://localhost:3000/problems/{slug}

# 检查控制台错误
list_console_messages

# 查看页面截图
take_screenshot -> /tmp/problem_{id}.png
```
