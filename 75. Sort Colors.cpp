class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count[4] = {0}, i;
        for (i = 0; i <nums.size(); ++i)
            count[nums[i]]++;
        i = 0;
        for (int j = 0; j <4; ++j) {
            while(count[j]--) nums[i++] = j;
        }
    }
};