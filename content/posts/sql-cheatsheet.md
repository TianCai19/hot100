---
title: "SQL LeetCode 常用语法速查"
difficulty: "文档"
description: "LeetCode 面试前快速复习 SQL 常用语法和查询技巧"
---

# SQL LeetCode 常用语法速查

## 📋 基础语法

### 基础查询
```sql
-- 基础 SELECT
SELECT column1, column2
FROM table_name;

-- 去重
SELECT DISTINCT column1
FROM table_name;

-- 条件查询
SELECT *
FROM table_name
WHERE condition1 AND/OR condition2;

-- 排序 (ASC 升序, DESC 降序)
SELECT *
FROM table_name
ORDER BY column1 ASC, column2 DESC;

-- 限制结果数量
SELECT *
FROM table_name
LIMIT 10 OFFSET 5;  -- 跳过前5行，取10行
```

### 条件判断
```sql
-- CASE WHEN (类似 if-else)
SELECT column1,
       CASE
           WHEN condition1 THEN value1
           WHEN condition2 THEN value2
           ELSE default_value
       END AS new_column
FROM table_name;

-- IF 函数 (MySQL)
SELECT IF(condition, value_if_true, value_if_false) AS result
FROM table_name;

-- NULL 处理
SELECT COALESCE(column1, 'default') AS result  -- 返回第一个非 NULL 值
FROM table_name;

SELECT column1, column2
FROM table_name
WHERE column1 IS NULL;  -- 查询 NULL 值

SELECT column1, column2
FROM table_name
WHERE column1 IS NOT NULL;  -- 查询非 NULL 值
```

## 📊 聚合函数与分组

### 常用聚合函数
```sql
-- 计数
SELECT COUNT(*) FROM table_name;           -- 总行数
SELECT COUNT(column1) FROM table_name;     -- 非 NULL 值数量
SELECT COUNT(DISTINCT column1) FROM table_name;  -- 去重计数

-- 求和、平均、最大、最小
SELECT SUM(column1) FROM table_name;
SELECT AVG(column1) FROM table_name;
SELECT MAX(column1) FROM table_name;
SELECT MIN(column1) FROM table_name;

-- 字符串聚合 (MySQL)
SELECT GROUP_CONCAT(column1 SEPARATOR ', ')
FROM table_name;

-- PostgreSQL
SELECT STRING_AGG(column1, ', ')
FROM table_name;
```

### GROUP BY 与 HAVING
```sql
-- 按列分组
SELECT column1, COUNT(*)
FROM table_name
GROUP BY column1;

-- 按多列分组
SELECT column1, column2, COUNT(*)
FROM table_name
GROUP BY column1, column2;

-- 分组后过滤 (HAVING 在 GROUP BY 之后执行)
SELECT column1, COUNT(*)
FROM table_name
GROUP BY column1
HAVING COUNT(*) > 10;

-- WHERE vs HAVING
SELECT column1, AVG(column2)
FROM table_name
WHERE column2 > 100      -- 在分组前过滤
GROUP BY column1
HAVING AVG(column2) > 200; -- 在分组后过滤
```

## 🔗 JOIN 操作

### 各种 JOIN
```sql
-- INNER JOIN (只返回匹配的行)
SELECT t1.column1, t2.column2
FROM table1 t1
INNER JOIN table2 t2 ON t1.id = t2.table1_id;

-- LEFT JOIN (返回左表所有行，右表不匹配为 NULL)
SELECT t1.column1, t2.column2
FROM table1 t1
LEFT JOIN table2 t2 ON t1.id = t2.table1_id;

-- RIGHT JOIN (返回右表所有行)
SELECT t1.column1, t2.column2
FROM table1 t1
RIGHT JOIN table2 t2 ON t1.id = t2.table1_id;

-- FULL OUTER JOIN (返回两表所有行，不匹配为 NULL)
SELECT t1.column1, t2.column2
FROM table1 t1
FULL OUTER JOIN table2 t2 ON t1.id = t2.table1_id;

-- CROSS JOIN (笛卡尔积)
SELECT t1.column1, t2.column2
FROM table1 t1
CROSS JOIN table2 t2;
```

### 自连接
```sql
-- 查找重复记录
SELECT t1.*
FROM table_name t1, table_name t2
WHERE t1.id != t2.id
  AND t1.column1 = t2.column1
  AND t1.column2 = t2.column2;

-- 查找有上下级关系的记录
SELECT e1.employee_id, e1.name, e2.name AS manager
FROM employees e1
LEFT JOIN employees e2 ON e1.manager_id = e2.employee_id;
```

## 📈 子查询与公用表表达式 (CTE)

### 子查询
```sql
-- 标量子查询 (返回单个值)
SELECT column1
FROM table1
WHERE column2 > (SELECT AVG(column2) FROM table2);

-- 列子查询 (返回单列多行)
SELECT column1
FROM table1
WHERE column2 IN (SELECT column2 FROM table2 WHERE condition);

-- 行子查询 (返回单行多列)
SELECT *
FROM table1
WHERE (column1, column2) = (SELECT column1, column2 FROM table2 WHERE id = 1);

-- EXISTS 子查询 (检查是否存在)
SELECT column1
FROM table1 t1
WHERE EXISTS (
    SELECT 1
    FROM table2 t2
    WHERE t2.id = t1.id
);
```

### 公用表表达式 (CTE)
```sql
-- 基础 CTE
WITH cte_name AS (
    SELECT column1, column2
    FROM table_name
    WHERE condition
)
SELECT *
FROM cte_name
WHERE column1 > 100;

-- 多重 CTE
WITH cte1 AS (
    SELECT column1, SUM(column2) AS total
    FROM table1
    GROUP BY column1
),
cte2 AS (
    SELECT column3, AVG(column4) AS avg_val
    FROM table2
    GROUP BY column3
)
SELECT cte1.column1, cte2.column3, cte1.total, cte2.avg_val
FROM cte1
JOIN cte2 ON cte1.column1 = cte2.column3;

-- 递归 CTE (LeetCode 中生成数字序列)
WITH RECURSIVE numbers AS (
    SELECT 1 AS n
    UNION ALL
    SELECT n + 1
    FROM numbers
    WHERE n < 100
)
SELECT n FROM numbers;
```

## 🔍 窗口函数

### 常用窗口函数
```sql
-- 行号 (ROW_NUMBER)
SELECT column1,
       ROW_NUMBER() OVER (ORDER BY column1) AS row_num
FROM table_name;

-- 排名 (RANK vs DENSE_RANK)
SELECT column1,
       ROW_NUMBER() OVER (ORDER BY column1) AS row_number,
       RANK() OVER (ORDER BY column1) AS rank,
       DENSE_RANK() OVER (ORDER BY column1) AS dense_rank
FROM table_name;

-- 分区统计 (PARTITION BY)
SELECT column1, column2,
       ROW_NUMBER() OVER (PARTITION BY column1 ORDER BY column2) AS row_num
FROM table_name;

-- 累计求和
SELECT column1, column2,
       SUM(column2) OVER (ORDER BY column1) AS cumulative_sum
FROM table_name;

-- 移动平均
SELECT column1, column2,
       AVG(column2) OVER (
           ORDER BY column1
           ROWS BETWEEN 2 PRECEDING AND CURRENT ROW
       ) AS moving_avg
FROM table_name;

-- 前后值
SELECT column1,
       LAG(column2, 1) OVER (ORDER BY column1) AS prev_value,
       LEAD(column2, 1) OVER (ORDER BY column1) AS next_value
FROM table_name;

-- 百分比排名
SELECT column1,
       PERCENT_RANK() OVER (ORDER BY column1) AS percent_rank
FROM table_name;

-- 分位数
SELECT column1,
       NTILE(4) OVER (ORDER BY column1) AS quartile
FROM table_name;
```

## 🔧 数据处理

### 字符串函数
```sql
-- 长度
SELECT LENGTH(column1) FROM table_name;

-- 截取
SELECT SUBSTRING(column1, 1, 5) FROM table_name;  -- 从位置1开始截取5个字符
SELECT LEFT(column1, 5) FROM table_name;         -- 左边5个字符
SELECT RIGHT(column1, 5) FROM table_name;        -- 右边5个字符

-- 查找和替换
SELECT INSTR(column1, 'substring') FROM table_name;  -- 返回位置
SELECT REPLACE(column1, 'old', 'new') FROM table_name;

-- 大小写转换
SELECT UPPER(column1), LOWER(column1) FROM table_name;

-- 去空格
SELECT TRIM(column1) FROM table_name;       -- 两边去空格
SELECT LTRIM(column1), RTRIM(column1) FROM table_name;  -- 左边/右边去空格

-- 拼接
SELECT CONCAT(column1, '-', column2) FROM table_name;
SELECT CONCAT_WS('-', column1, column2, column3) FROM table_name;  -- 用分隔符拼接
```

### 数值函数
```sql
-- 绝对值、四舍五入
SELECT ABS(-10), ROUND(3.14159, 2) FROM table_name;

-- 幂、开方
SELECT POWER(2, 3), SQRT(16) FROM table_name;

-- 取整
SELECT CEIL(3.14), FLOOR(3.14) FROM table_name;

-- 随机数
SELECT RAND() FROM table_name;  -- 0-1之间的随机数
SELECT RAND() * 100 FROM table_name;  -- 0-100之间的随机数
```

### 日期时间函数
```sql
-- 当前时间
SELECT NOW(), CURRENT_DATE, CURRENT_TIME FROM table_name;

-- 日期计算
SELECT DATE_ADD('2023-01-01', INTERVAL 30 DAY) FROM table_name;
SELECT DATEDIFF('2023-01-31', '2023-01-01') FROM table_name;

-- 提取部分
SELECT YEAR('2023-05-15'), MONTH('2023-05-15'), DAY('2023-05-15') FROM table_name;
SELECT DAYOFWEEK('2023-05-15') FROM table_name;  -- 1-7 (周日=1)

-- 格式化
SELECT DATE_FORMAT('2023-05-15', '%Y-%m-%d') FROM table_name;
SELECT TIME_FORMAT('12:30:45', '%h:%i %p') FROM table_name;
```

## 📊 高级技巧

### 排名问题
```sql
-- Top K 问题
SELECT *
FROM table_name
ORDER BY column1 DESC
LIMIT 10;

-- 第 N 高的值
SELECT DISTINCT column1
FROM table_name
ORDER BY column1 DESC
LIMIT 1 OFFSET N-1;

-- 中位数
SELECT AVG(column1) AS median
FROM (
    SELECT column1,
           ROW_NUMBER() OVER (ORDER BY column1) AS row_asc,
           ROW_NUMBER() OVER (ORDER BY column1 DESC) AS row_desc
    FROM table_name
) t
WHERE row_asc IN (row_desc, row_desc + 1, row_desc - 1);

-- 连续出现
SELECT DISTINCT column1
FROM (
    SELECT column1,
           column1 - ROW_NUMBER() OVER (ORDER BY column1) AS grp
    FROM table_name
) t
GROUP BY column1, grp
HAVING COUNT(*) >= 3;
```

### 分组统计
```sql
-- 每个分组的 Top 1
SELECT t1.*
FROM table_name t1
WHERE column1 = (
    SELECT MAX(column1)
    FROM table_name t2
    WHERE t2.group_column = t1.group_column
);

-- 或使用窗口函数
SELECT *
FROM (
    SELECT *,
           ROW_NUMBER() OVER (PARTITION BY group_column ORDER BY column1 DESC) AS rn
    FROM table_name
) t
WHERE rn = 1;

-- 每组的累计统计
SELECT column1,
       SUM(column2) OVER (
           PARTITION BY column1
           ORDER BY date_column
           ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
       ) AS cumulative_sum
FROM table_name;
```

### 去重与合并
```sql
-- 去重 (多列)
SELECT DISTINCT column1, column2, column3
FROM table_name;

-- 按组合并
SELECT column1,
       GROUP_CONCAT(column2 SEPARATOR ', ')
FROM table_name
GROUP BY column1;

-- 查找重复记录
SELECT column1, COUNT(*)
FROM table_name
GROUP BY column1
HAVING COUNT(*) > 1;
```

## 🚀 性能优化技巧

### 索引使用
```sql
-- 确保 WHERE 子句使用索引列
SELECT *
FROM table_name
WHERE indexed_column = value;

-- 避免在函数中使用索引列
-- 慢: WHERE YEAR(date_column) = 2023
-- 快: WHERE date_column >= '2023-01-01' AND date_column < '2024-01-01'
```

### 查询优化
```sql
-- 使用 EXISTS 替代 IN (某些情况下)
SELECT column1
FROM table1 t1
WHERE EXISTS (
    SELECT 1
    FROM table2 t2
    WHERE t2.id = t1.id
);

-- 避免 SELECT *
SELECT column1, column2
FROM table_name
WHERE column1 = value;

-- 使用 LIMIT 限制结果
SELECT column1
FROM table_name
WHERE condition
LIMIT 1000;
```

## 🎯 LeetCode 常用模式

### 1. 排名问题
```sql
-- 工资排名
SELECT Salary,
       DENSE_RANK() OVER (ORDER BY Salary DESC) AS rank
FROM Employee;

-- 每部门工资排名
SELECT Dept, Salary,
       DENSE_RANK() OVER (PARTITION BY Dept ORDER BY Salary DESC) AS rank
FROM Employee;
```

### 2. Top K 问题
```sql
-- 最高的 3 个薪资
SELECT DISTINCT Salary
FROM Employee
ORDER BY Salary DESC
LIMIT 3;

-- 第 3 高的薪资
SELECT DISTINCT Salary
FROM Employee
ORDER BY Salary DESC
LIMIT 1 OFFSET 2;
```

### 3. 连续问题
```sql
-- 连续登录天数
SELECT DISTINCT consecutive_days
FROM (
    SELECT date,
           date - ROW_NUMBER() OVER (ORDER BY date) AS grp
    FROM Logins
) t
GROUP BY grp, consecutive_days
ORDER BY MAX(consecutive_days) DESC
LIMIT 1;
```

### 4. 累计问题
```sql
-- 累计销售额
SELECT date,
       sales,
       SUM(sales) OVER (ORDER BY date) AS cumulative_sales
FROM Sales;
```

### 5. 合并分组
```sql
-- 每部门员工姓名合并
SELECT Dept,
       STRING_AGG(Name, ', ') AS Employees
FROM Employee
GROUP BY Dept;
```

### 6. 条件统计
```sql
-- 每月订单数
SELECT DATE_FORMAT(OrderDate, '%Y-%m') AS month,
       COUNT(*) AS order_count
FROM Orders
GROUP BY DATE_FORMAT(OrderDate, '%Y-%m')
ORDER BY month;
```

### 7. 缺失日期补全
```sql
-- 生成日期序列并左连接
WITH RECURSIVE dates AS (
    SELECT '2023-01-01' AS date
    UNION ALL
    SELECT date + INTERVAL 1 DAY
    FROM dates
    WHERE date < '2023-01-31'
)
SELECT d.date, COUNT(o.id) AS order_count
FROM dates d
LEFT JOIN Orders o ON DATE(o.OrderDate) = d.date
GROUP BY d.date
ORDER BY d.date;
```

## 📝 注意事项

1. **NULL 值处理**: NULL 与任何值比较都是 NULL，需要使用 IS NULL 或 IS NOT NULL
2. **数据类型**: 不同数据库的函数名可能有差异（如字符串拼接、日期函数）
3. **性能**: 大表查询时注意使用索引，避免 SELECT *
4. **子查询优化**: 尽量使用 JOIN 或 EXISTS 替代 IN 子查询
5. **窗口函数**: 只有支持窗口函数的数据库（如 MySQL 8.0+、PostgreSQL）才能使用
