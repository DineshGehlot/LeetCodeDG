class Solution {
public:
    int search(vector<int>& nums, int target) 
    {
        int i = 0, j = nums.size()-1, mid;
        while(i<=j)
        {
            mid = i + (j-i)/2;
            if(nums[mid]==target) return mid;
            
            if(nums[i]<=nums[mid]) // left side not rotated
            {
                if(nums[i]<=target && target<nums[mid]) j = mid-1; // check it target withing left side range
                else i = mid+1;
            }
            else // right side is not rotated
            {
                if(nums[mid]<target && target<= nums[j]) i = mid+1;
                else j = mid-1;
            }
        }
         return -1;
    }
};


/*
Also Working:

class Solution {
    int t;
    int findRotIndex(vector<int>& nums, int i, int j) {
        if(i==j) return i;
        int mid = i + (j-i)/2;
        if(nums[mid]>nums[j]) return findRotIndex(nums,mid+1,j);
        return findRotIndex(nums,i, mid);
    }
    int bSearch(vector<int>& nums, int i, int j) {
        if(i>j) return -1;
        int mid = i + (j-i)/2;
        if(nums[mid]==t) return mid;
        if(nums[mid]>t) return bSearch(nums,i, mid-1);
        else return bSearch(nums,mid+1, j);
    }
public:
    int search(vector<int>& nums, int target) {
        int rotIndex = findRotIndex(nums, 0, nums.size()-1);
        t = target;
        if(target<=nums[nums.size()-1]) return bSearch(nums,rotIndex, nums.size()-1);
        return bSearch(nums,0, rotIndex-1);
    }
};

 */