class Solution(object):
    def twoSum(self, nums, target):
        num_hash = {}
        n = len(nums)

        for i in range(n):
            subtracted_num = target - nums[i]
            if subtracted_num  in num_hash:
                return [num_hash[subtracted_num], i]
            num_hash[nums[i]] = i
        return []

solution = Solution()

# Test case 1:
nums1 = [2, 7, 11, 15]
target1 = 9
result1 = solution.twoSum(nums1, target1)
print(result1) 

# Test case 2:
nums2 = [3, 5, 8, 12]
target2 = 22
result2 = solution.twoSum(nums2, target2)
print(result2)  

# Test case 3: 
nums3 = [-1, -5, 8, 20]
target3 = -6
result3 = solution.twoSum(nums3, target3)
print(result3) 

# Test case 4: 
nums4 = []
target4 = 5
result4 = solution.twoSum(nums4, target4)
print(result4) 

# Test case 5: 
nums5 = [1, 2, 3, 4, 6, 8]
target5 = 7
result5 = solution.twoSum(nums5, target5)
print(result5)

# Runtime 45 ms and 14.28 MB
