class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = nums[0], i;
        for (int i = 0; i <=reach; ++i) {
            reach = max(reach, i + nums[i]);
            if (reach >= nums.size()-1) return true;
        }
        return false;
    }
};