# ## Solution 1
# class Solution(object):
#     def productExceptSelf(self, nums):
#         list1=[]
#         list2=[]
#         product_forward=1
#         product_backward=1
#         nums1=nums[::-1]

#         for i in range(len(nums)-1, 0, -1):
#             product_forward*=nums[i] 
#             list1.insert(0, product_forward)
#             product_backward*=nums1[i] 
#             list2.insert(0, product_backward) 
#         list1.append(1)
#         list2.append(1)
#         list2=list2[::-1]

#         res_list=[]
#         for i in range(0, len(list1)):
#             res_list.append(list1[i]*list2[i])
#         return res_list
    
## Solution 2

class Solution:
    def productExceptSelf(self, nums):
        res=[]
        
        acc=1
        for n in nums:
            res.append(acc)
            acc*=n

        acc=1
        for i in reversed(range(len(nums))):
            res[i]*=acc
            acc*=nums[i]
            
        return res

# Test Case 1:
s1 = Solution()
nums1 = [1, 2, 3, 4]
result1 = s1.productExceptSelf(nums1)
print(result1)

# Test Case 2:
s2 = Solution()
nums2 = [5, 2, 7, 1]
result2 = s2.productExceptSelf(nums2)
print(result2)

# Test Case 3:
s3 = Solution()
nums3 = [3, 9, 2, 4]
result3 = s3.productExceptSelf(nums3)
print(result3)

# Test Case 4:
s4 = Solution()
nums4 = [2, 1, 5, 6]
result4 = s4.productExceptSelf(nums4)
print(result4)

# Test Case 5:
s5 = Solution()
nums5 = [8, 2, 1, 6]
result5 = s5.productExceptSelf(nums5)
print(result5)

