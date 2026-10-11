class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map <int,int> mp;
        int ans = 0, currSum =0;
        mp[0] = 1; // Zero already appeared once.
        for (int i =0 ; i < nums.size(); ++i) {
            currSum += nums[i];
            
            if(mp[currSum-k])
                ans += (mp[currSum-k]);
            mp[currSum]++;
        }
        return ans;
    }
};
