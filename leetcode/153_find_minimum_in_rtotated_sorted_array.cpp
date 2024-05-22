class Solution {
public:
    int findMin(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return nums[0];
        }
        if (nums[0] < nums[len - 1])
            return nums[0];
        // at least 2 elements
        int left = 0, right = len - 1;
        while (!((right - left < 2) || (nums[left] < nums[right]))) {
            int mid = left + (right - left) / 2;
            if (nums[left] < nums[mid] && nums[mid] > nums[right]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (nums[left] < nums[right]) {
            return nums[left];
        } else {
            return nums[right];
        }
    }
};
