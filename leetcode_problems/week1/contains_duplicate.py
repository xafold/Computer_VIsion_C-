class Solution(object):
    def containsDuplicate(self, nums):
        if len(nums) == len(set(nums)):
            return False
        return True  
solution = Solution()

# Test case 1:
num1 = [1, 2, 3, 4, 5, 6, 7]
result1 = solution.containsDuplicate(num1)
print(result1) 

# Test case 2:
num2 = [1, 2, 3, 4, 5, 5, 3, 2]
result2 = solution.containsDuplicate(num2)
print(result2)

# Test case 3:
num3 = []
result3 = solution.containsDuplicate(num3)
print(result3)

# Runtime is 414 ms and Memory is 28.9 MB 