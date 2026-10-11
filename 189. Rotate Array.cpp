class Solution {
    void reverse(vector<int>& nums, int i, int j){
        while(i<j) {
            swap(nums[i++],nums[j--]);
        }
    }
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = n - (k % n);
        reverse(nums,0,n-1);
        reverse(nums,0,n-1-k);
        reverse(nums,n-k,nums.size()-1);
    }
};
