int removeDuplicates(int* nums, int numsSize) {
    int i = 0, j = 0;
    while (j < numsSize) {
        nums[i] = nums[j];
        ++i;
        if(j+1 < numsSize && nums[j]==nums[j+1]) {
             nums[i] = nums[j];
             ++i;
        }
        while(j+1 < numsSize && nums[j]==nums[j+1]) ++j;
        ++j;
    }
    return i;
}
