# Solution 1
class Solution:
    def twoSum(self, numbers, target):
        left_pointer, right_pointer = 0, len(numbers)-1

        while left_pointer < right_pointer:
            sum = numbers[left_pointer] + numbers[right_pointer]
            if sum > target:
                right_pointer -=1
            elif sum < target:
                left_pointer +=1
            else:
                return [left_pointer+1, right_pointer+1]


            

# Test Case 1:
s1 = Solution()
numbers1 = [2, 7, 11, 15]
target1 = 9
result1 = s1.twoSum(numbers1, target1)
print(result1)

# Test Case 2:
s2 = Solution()
numbers2 = [2, 3, 4]
target2 = 6
result2 = s2.twoSum(numbers2, target2)
print(result2)

# Test Case 3:
s3 = Solution()
numbers3 = [1, 2, 3, 4, 5]
target3 = 6
result3 = s3.twoSum(numbers3, target3)
print(result3)

# Test Case 4:
s4 = Solution()
numbers4 = [-4, -1, 0, 2, 5, 6, 8, 10]
target4 = 8
result4 = s4.twoSum(numbers4, target4)
print(result4)

# Test Case 5:
s5 = Solution()
numbers5 = [-2, 0, 1, 3, 5]
target5 = 4
result5 = s5.twoSum(numbers5, target5)
print(result5)
