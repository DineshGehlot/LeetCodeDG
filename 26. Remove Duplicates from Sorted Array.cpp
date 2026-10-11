class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int k = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if(nums[i] != nums[k]) {
                k+=1;
                nums[k] = nums[i];
            }
        }
        return k+1;
    }
};

/*
Also works:

int removeDuplicates(int* nums, int numsSize) {
    int i = 0, j = 0;
    while(j<numsSize) {
        while(j+1<numsSize && nums[j] == nums[j+1]) ++j;
        nums[i] = nums[j];
        ++j; ++i;
    }
    return i;
}
*/