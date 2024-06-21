## Solution 1
from collections import defaultdict


class Solution(object):
    def groupAnagrams(self, strs):
        hash_map = {}
        for word in strs:
            sorted_word = ''.join(sorted(word)) 
            
            if sorted_word not in hash_map:
                hash_map[sorted_word] = []
            
            hash_map[sorted_word].append(word)
        
        return hash_map

## Solution 2
# class Solution(object):
#     def groupAnagrams(self, strs):
#         hash_map = defaultdict(list)
#         for word in strs:
#             sorted_word = ''.join(sorted(word))
#             hash_map[sorted_word].append(word)
        
#         return hash_map

## TEST CASES

sol = Solution()

# Test Case 1:
strs1 = ["eat", "tea", "tan", "ate", "nat", "bat"]
result1 = sol.groupAnagrams(strs1)
print(result1)

# Test Case 2:
strs2 = []
result2 = sol.groupAnagrams(strs2)
print(result2)

# Test Case 3:
strs3 = ["hello"]
result3 = sol.groupAnagrams(strs3)
print(result3)

# Test Case 4:
strs4 = ["abc", "def", "xyz"]
result4 = sol.groupAnagrams(strs4)
print(result4)

# Test Case 5:
strs5 = ["Listen", "Silent", "Triangle", "Integral"]
result5 = sol.groupAnagrams(strs5)
print(result5)
