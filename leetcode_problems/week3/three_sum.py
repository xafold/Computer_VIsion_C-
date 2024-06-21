# # Solution 1 using set
# class Solution:
#     def threeSum(self, nums):
#         nums.sort()
#         triplets = set()

#         for i in range(len(nums)-2):
#             # Skips if we find the duplicate elements found current vs previous element
#             if i > 0 and nums[i] == nums[i-1]:
#                 continue

#             left_pointer, right_pointer = i + 1, len(nums) - 1

#             while left_pointer < right_pointer:
#                 total_sum = nums[i] + nums[left_pointer] + nums[right_pointer]
#                 if total_sum > 0:
#                     right_pointer -= 1
#                 elif total_sum< 0:
#                     left_pointer += 1
#                 else:
#                     triplets.add((nums[i], nums[left_pointer], nums[right_pointer]))
#                     left_pointer, right_pointer = left_pointer + 1, right_pointer - 1

#         return list(triplets)

# Solution 2 using only list
class Solution:
    def threeSum(self, nums):
        nums.sort()
        three_sum = []

        for i in range(len(nums)-2):
            # Skips if we find duplicate elements comparing the current and previous elements
            if i > 0 and nums[i] == nums[i-1]:
                continue

            left_pointer, right_pointer = i + 1, len(nums) - 1

            while left_pointer < right_pointer:
                total_sum = nums[i] + nums[left_pointer] + nums[right_pointer]
                if total_sum > 0:
                    right_pointer -= 1
                elif total_sum < 0:
                    left_pointer += 1
                else:
                    three_sum.append([nums[i], nums[left_pointer], nums[right_pointer]])
                    # Skip duplicates for left_pointer
                    while left_pointer < right_pointer and nums[left_pointer] == nums[left_pointer + 1]:
                        left_pointer += 1
                    # Skip duplicates for right_pointer
                    while left_pointer < right_pointer and nums[right_pointer] == nums[right_pointer - 1]:
                        right_pointer -= 1
                    left_pointer, right_pointer = left_pointer + 1, right_pointer - 1

        return three_sum

# Test Case 1:
s1 = Solution()
nums1 = [-1, 0, 1, 2, -1, -4]
result1 = s1.threeSum(nums1)
print(result1)

# Test Case 2:
s2 = Solution()
nums2 = [0, 0, 0]
result2 = s2.threeSum(nums2)
print(result2)

# Test Case 3:
s3 = Solution()
nums3 = [-2, 0, 0, 2, 2]
result3 = s3.threeSum(nums3)
print(result3)

# Test Case 4:
s4 = Solution()
nums4 = [3, 0, -2, -1, 1, 2]
result4 = s4.threeSum(nums4)
print(result4)

# Test Case 5:
s5 = Solution()
nums5 = [0,1,1]
result5 = s5.threeSum(nums5)
print(result5)

