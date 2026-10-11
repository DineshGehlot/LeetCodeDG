class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int i = 0, j = nums.size()-1, first = -1, second = -1, mid;

        while (i <= j) {
            mid = i + (j-i)/2;
            if (nums[mid]==target) first = mid;
            if (nums[mid]>=target) j = mid - 1;
            else  i = mid+1;
        }
        if (first == -1) return {-1,-1};
        j = nums.size() - 1;
        i = first;
        while (i<=j) {
            mid = i + (j-i)/2;
            if (nums[mid]==target) second = mid;
            if (nums[mid]<= target) i = mid + 1; 
            else j = mid-1;
        }

        return {first, second};
    }
};