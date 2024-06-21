class Solution:
    def maxArea(self, height) -> int:
        result = []
        left_pointer, right_pointer = 0, len(height)-1
        while left_pointer < right_pointer:
            if height[left_pointer] > height[right_pointer]:
                area = (right_pointer - left_pointer) * height[right_pointer]
                result.append(area)
                right_pointer -= 1
            else:
                area = (right_pointer - left_pointer) * height[left_pointer]
                result.append(area)
                left_pointer += 1
        result.sort(reverse=True)
        return result[0]

# Test Case 1
s1 = Solution()
heights1 = [1, 8, 6, 2, 5, 4, 8, 3, 7]
result1 = s1.maxArea(heights1)
print(result1)
# Expected Output: 49

# Test Case 2
s2 = Solution()
heights2 = [2, 2]
result2 = s2.maxArea(heights2)
print(result2)
# Expected Output: 2

# Test Case 3
s3 = Solution()
heights3 = [1, 2, 3, 4, 5]
result3 = s3.maxArea(heights3)
print(result3)
# Expected Output: 6

# Test Case 4
s4 = Solution()
heights4 = [5, 4, 3, 2, 1]
result4 = s4.maxArea(heights4)
print(result4)
# Expected Output: 6

# Test Case 5
s5 = Solution()
heights5 = [3, 1, 2, 4, 5, 3, 2, 1, 4, 6, 2, 1, 5, 6]
result5 = s5.maxArea(heights5)
print(result5)
# Expected Output: 30
