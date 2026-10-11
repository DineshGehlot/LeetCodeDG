class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i =0, j = 0, minLen = INT_MAX;
        unsigned int currSum = nums[i], n = nums.size();
        while (j < n && i < n) {
            if (currSum >= target) {
                minLen = min(j-i+1, minLen);
                currSum -= nums[i];
                ++i;
            } else {
                ++j;
                if(j<n) currSum += nums[j];
            }
        }
        return (minLen==INT_MAX)?0:minLen;
    }
};


/* Also works:

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i =0, j = 0, minLen = INT_MAX;
        unsigned int currSum = 0;
        while (j < nums.size() || i < nums.size()) {
            if((j < nums.size()) && currSum < target) {
                currSum += nums[j];
                ++j;
            } else {
                currSum -= nums[i];
                ++i;
            }
            if (currSum >= target) {
                minLen = min((j-i), minLen);
            }
        }
        return (minLen==INT_MAX)?0:minLen;
    }
};

*/