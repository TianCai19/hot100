from typing import List

def merge(intervals: List[List[int]]) -> List[List[int]]:
    """
    合并区间 - 排序后合并

    时间复杂度: O(n log n)，排序的时间复杂度
    空间复杂度: O(1)，不计输出空间
    """
    if not intervals or not intervals[0]:
        return []

    # 按区间起始位置排序
    intervals.sort(key=lambda x: x[0])

    merged = []
    for interval in intervals:
        # 如果列表为空，或者当前区间不与前一个区间重叠
        if not merged or interval[0] > merged[-1][1]:
            merged.append(interval)
        else:
            # 当前区间与前一个区间重叠，合并它们
            merged[-1][1] = max(merged[-1][1], interval[1])

    return merged

# 测试用例
if __name__ == "__main__":
    test_cases = [
        ([[1,3],[2,6],[8,10],[15,18]], [[1,6],[8,10],[15,18]]),
        ([[1,4],[4,5]], [[1,5]]),
        ([[1,4],[2,3]], [[1,4]]),
        ([[]], []),
        ([[1,4],[0,4]], [[0,4]]),
        ([[1,4],[2,3],[5,7],[6,8]], [[1,4],[5,8]])
    ]

    for i, (input_intervals, expected) in enumerate(test_cases, 1):
        result = merge(input_intervals)
        print(f"测试用例 {i}: {'通过' if result == expected else '失败'}")
        print(f"  输入: {input_intervals}")
        print(f"  输出: {result}")
        print(f"  预期: {expected}\n")
