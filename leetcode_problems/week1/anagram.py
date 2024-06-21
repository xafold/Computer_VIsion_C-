class Solution(object):
    def isAnagram(self, s, t):
        if len(s) != len(t):
            return False
        return all(s.count(i) == t.count(i) for i in set(s))

solution = Solution()

# Test case 1:
s1 = "listen"
t1 = "silent"
result1 = solution.isAnagram(s1, t1)
print(result1)

# Test case 2:
s2 = "triangle"
t2 = "integral"
result2 = solution.isAnagram(s2, t2)
print(result2)

# Test case 3:
s3 = "hello"
t3 = "world"
result3 = solution.isAnagram(s3, t3)
print(result3) 

# Test case 4:
s4 = "aab"
t4 = "aba"
result4 = solution.isAnagram(s4, t4)
print(result4)

