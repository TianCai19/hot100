---
title: "215. 数组中的第 K 个最大元素"
difficulty: "中等"
description: "给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。"
---

# 215. 数组中的第 K 个最大元素

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定整数数组 `nums` 和整数 `k`，请返回数组中第 `k` 个最大的元素。

请注意，你需要找到的是第 `k` 个最大的元素，而不是第 `k` 个不同的元素。

### 示例

**示例 1：**
```
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
```

**示例 2：**
```
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
```

### 提示

- `1 <= k <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`

---

## 解法一：排序法（简单直观）

### 思路

直接对数组进行降序排序，然后返回第 `k` 个元素。时间复杂度 `O(n log n)`，思路简单直接。

### Python

```python
from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        # 降序排序
        nums.sort(reverse=True)
        # 返回第 k 个最大元素（索引为 k-1）
        return nums[k - 1]
```

### C++

```cpp
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 降序排序
        sort(nums.begin(), nums.end(), greater<int>());
        // 返回第 k 个最大元素
        return nums[k - 1];
    }
};
```

### 复杂度分析

- **时间复杂度：** `O(n log n)`，排序需要 `O(n log n)` 时间
- **空间复杂度：** `O(1)`（如果使用原地排序）或 `O(n)`（如果使用额外空间）

---

## 解法二：堆排序 - 最小堆（推荐）

### 思路

使用最小堆维护前 `k` 个最大元素。遍历数组：
1. 将元素加入最小堆
2. 如果堆大小超过 `k`，弹出堆顶元素（最小的）
3. 遍历结束后，堆顶就是第 `k` 个最大元素

**为什么使用最小堆？**
- 堆顶始终是当前 `k` 个最大元素中的最小值
- 保持堆大小为 `k`，不需要存储所有元素

### Python

```python
import heapq
from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        # 最小堆
        min_heap = []

        for num in nums:
            # 将元素加入堆
            heapq.heappush(min_heap, num)

            # 如果堆大小超过 k，弹出最小元素
            if len(min_heap) > k:
                heapq.heappop(min_heap)

        # 堆顶就是第 k 个最大元素
        return min_heap[0]
```

### C++

```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 最小堆（priority_queue 默认是最小堆的比较器）
        priority_queue<int, vector<int>, greater<int>> min_heap;

        for (int num : nums) {
            // 将元素加入堆
            min_heap.push(num);

            // 如果堆大小超过 k，弹出最小元素
            if ((int)min_heap.size() > k) {
                min_heap.pop();
            }
        }

        // 堆顶就是第 k 个最大元素
        return min_heap.top();
    }
};
```

### 复杂度分析

- **时间复杂度：** `O(n log k)`，每个元素入堆出堆最多 `log k` 时间
- **空间复杂度：** `O(k)`，只需要存储 `k` 个元素

---

## 解法三：快速选择算法（基于快速排序）

### 思路

基于快速排序的思想，通过划分（partition）找到第 `k` 大的元素：

1. 选择基准元素，将数组划分为两部分
2. 根据基准元素的位置判断目标位置
3. 递归处理目标部分

### Python

```python
from typing import List
import random

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        n = len(nums)
        # 转换为寻找第 (n-k) 小元素
        target = n - k

        def partition(left: int, right: int, pivot_index: int) -> int:
            pivot = nums[pivot_index]
            # 1. 将基准元素移到末尾
            nums[pivot_index], nums[right] = nums[right], nums[pivot_index]
            store_index = left

            # 2. 将所有比基准大的元素移到左边
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[store_index], nums[i] = nums[i], nums[store_index]
                    store_index += 1

            # 3. 将基准元素移回正确位置
            nums[right], nums[store_index] = nums[store_index], nums[right]
            return store_index

        def quickselect(left: int, right: int) -> int:
            if left == right:
                return nums[left]

            # 随机选择基准元素
            pivot_index = random.randint(left, right)
            pivot_index = partition(left, right, pivot_index)

            # 基准元素的位置
            if pivot_index == target:
                return nums[pivot_index]
            elif pivot_index < target:
                return quickselect(pivot_index + 1, right)
            else:
                return quickselect(left, pivot_index - 1)

        return quickselect(0, n - 1)
```

### C++

```cpp
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int target = n - k;

        function<int(int, int)> quickselect = [&](int left, int right) -> int {
            if (left == right) {
                return nums[left];
            }

            // 随机选择基准元素
            int pivot_index = left + rand() % (right - left + 1);
            pivot_index = partition(nums, left, right, pivot_index);

            if (pivot_index == target) {
                return nums[pivot_index];
            } else if (pivot_index < target) {
                return quickselect(pivot_index + 1, right);
            } else {
                return quickselect(left, pivot_index - 1);
            }
        };

        return quickselect(0, n - 1);
    }

private:
    int partition(vector<int>& nums, int left, int right, int pivot_index) {
        int pivot = nums[pivot_index];
        // 1. 将基准元素移到末尾
        swap(nums[pivot_index], nums[right]);
        int store_index = left;

        // 2. 将所有比基准大的元素移到左边
        for (int i = left; i < right; i++) {
            if (nums[i] < pivot) {
                swap(nums[store_index], nums[i]);
                store_index++;
            }
        }

        // 3. 将基准元素移回正确位置
        swap(nums[right], nums[store_index]);
        return store_index;
    }
};
```

### 复杂度分析

- **平均时间复杂度：** `O(n)`
- **最坏时间复杂度：** `O(n²)`（当每次划分的基准都是最小/最大元素时）
- **空间复杂度：** `O(1)`（原地算法）

---

## 三种解法对比

| 解法 | 时间复杂度（平均） | 空间复杂度 | 优点 | 缺点 |
|------|------------------|-----------|------|------|
| 排序法 | O(n log n) | O(1) | 思路简单，实现容易 | 不是最优，时间复杂度较高 |
| 最小堆 | O(n log k) | O(k) | 适合处理大量数据，空间效率高 | 需要维护堆结构 |
| 快速选择 | O(n) | O(1) | 平均性能最优 | 最坏情况性能差，实现复杂 |

## 总结

- **堆解法**是最实用的解法，平衡了性能和实现复杂度
- **快速选择**在追求最优平均性能时使用
- **排序法**在需要完整排序结果时使用（返回第 k 大后，还需要后续元素）
