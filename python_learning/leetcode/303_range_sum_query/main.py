#I've decided to use leetcode as a way to warm up to python as I relearn it (last time I used it was in high school)
# This is my first one, while not as efficient as other leetcode examples, it helped me learn a bit of the class based syntax and how it compares to C++

class NumArray(object):
    numbers = []

    def __init__(self, nums):
        self.numbers = nums
        """
        :type nums: List[int]
        """
        

    def sumRange(self, left, right):
        sum = 0
        for i in range(left, right + 1):
            sum += self.numbers[i]
        return sum
        """
        :type left: int
        :type right: int
        :rtype: int
        """

nums = [-2, 0, 3, -5, 2, -1]
left = 0
right = 2
        
obj = NumArray(nums)
param_1 = obj.sumRange(left,right)
print(param_1)
# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# param_1 = obj.sumRange(left,right)
