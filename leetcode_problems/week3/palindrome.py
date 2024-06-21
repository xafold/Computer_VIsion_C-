# ## Solution 1
# class Solution:
#     def isPalindrome(self, s: str):
#         clean_string = [c for c in s if c.isalnum()]
#         a = "".join(clean_string).lower()
#         if len(a)%2 == 0:
#             return a[:(len(a)//2)] == a[-1:-(len(a)//2+1):-1]
#         else:
#             return a[:(len(a)//2)] == a[-1:-(len(a)//2+1):-1]
    
## Solution 2
class Solution:
    def isPalindrome(self, s: str):
        a = [c.lower() for c in s if c.isalnum()]
        left_pointer, right_pointer = 0, len(a)-1
        while left_pointer < right_pointer:
            if a[left_pointer] != a[right_pointer]:
                return False
            left_pointer += 1
            right_pointer -= 1
        return True

# Test Case 1:
s1 = Solution()
string1 = "A man, a plan, a canal, Panama!"
result1 = s1.isPalindrome(string1)
print(result1)

# Test Case 2:
s2 = Solution()
string2 = "race a car"
result2 = s2.isPalindrome(string2)
print(result2)

# Test Case 3:
s3 = Solution()
string3 = "Was it a car or a cat I saw?"
result3 = s3.isPalindrome(string3)
print(result3)

# Test Case 4:
s4 = Solution()
string4 = "No lemon, no melon"
result4 = s4.isPalindrome(string4)
print(result4)

# Test Case 5:
s5 = Solution()
string5 = "Step on no pets"
result5 = s5.isPalindrome(string5)
print(result5)


