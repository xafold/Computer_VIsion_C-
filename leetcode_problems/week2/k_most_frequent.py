## Solution 1
class Solution(object):
    def topKFrequent(self, nums, k):
        hash_map = {}
        list = []
        for num in nums:
            if num not in hash_map:
                hash_map[num] = 0
            hash_map[num] += 1
        sorted_items = sorted(hash_map.items(), key=lambda x: x[1], reverse=True)
        for i in range(k):
            list.append(sorted_items[i][0])
        return list  

# Test Case 1:
s1 = Solution()
nums = [1, 1, 1, 2, 2, 3]
k = 2
result = s1.topKFrequent(nums, k)
print(result)

# Test Case 2:
s2 = Solution()
nums2 = [1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
k2 = 3
result2 = s2.topKFrequent(nums2, k2)
print(result2)

# Test Case 3:
s3 = Solution()
nums3 = [5, 5, 5, 1, 1, 2, 2, 3, 3, 4]
k3 = 1
result3 = s3.topKFrequent(nums3, k3)
print(result3)

# Test Case 4:
s4 = Solution()
nums4 = [1, 2, 3, 4, 5]
k4 = 5
result4 = s4.topKFrequent(nums4, k4)
print(result4)

# Test Case 5:
s5 = Solution()
nums5 = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
k5 = 4
result5 = s5.topKFrequent(nums5, k5)
print(result5)
