class Solution {
public:
    int search(vector<int>& nums, int target) {
     int i = 0, j = nums.size()-1, mid;
     while(i<=j) {
        mid = i + (j-i)/2;
        if(nums[mid]==target) return mid;
        if(nums[mid]>target) j = mid -1;
        else i = mid + 1;
     }
     return -1;
    }
};

/*

Also works:

class Solution {
    int binarySearch(int i, int j, vector<int>& nums, int target) {
        if(i<0 || j >= nums.size() || j<i) return -1;
        int mid = i + (j-i)/2;

        if (nums[mid] == target) return mid;
        
        if (nums[mid]>target) return binarySearch(i, mid-1, nums, target);
        return binarySearch(mid + 1, j, nums, target);
    }
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(0, nums.size()-1, nums, target);
    }
};

*/