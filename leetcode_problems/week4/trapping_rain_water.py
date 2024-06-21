class Solution:
    def trap(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        left_max, right_max = height[left], height[right]
        result = 0

        while left < right:
            if left_max < right_max:
                left += 1
                left_max = max(left_max, height[left])
                result += max(0, left_max - height[left])
            else:
                right -= 1
                right_max = max(right_max, height[right])
                result += max(0, right_max - height[right])

        return result
    
# Test Case 1:
s1 = Solution()
height1 = [0,1,0,2,1,0,1,3,2,1,2,1]
result1 = s1.trap(height1)
print(result1)

# Test Case 2:
s2 = Solution()
height2 = [4,2,0,3,2,5]
result2 = s2.trap(height2)
print(result2)

# Test Case 3:
s3 = Solution()
height3 = [3,1,3,4,2,2,1,2,1]
result3 = s3.trap(height3)
print(result3)

# Test Case 4:
s4 = Solution()
height4 = [1,2,3,4,5]
result4 = s4.trap(height4)
print(result4)

# Test Case 5:
s5 = Solution()
height5 = [5,4,3,2,1]
result5 = s5.trap(height5)
print(result5)
