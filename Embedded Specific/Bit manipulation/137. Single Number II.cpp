class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0, count;
        unsigned int mask;
        for (int i = 0; i <=31; ++i) {
            count = 0;
            mask = 1U << i;
            for(int n : nums) if (n & mask) ++count;
            if (count%3) ans |= mask;
        }
        return ans;
    }
};


// Can also be solved as 3 state
// 00 and 11 never appears or appeard multiple of 3 times
//  01 appears once, 10 appears twice

/*
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (int x : nums) {
            ones = (ones ^ x) & ~twos;
            twos = (twos ^ x) & ~ones;
        }
        return ones;
    }


*/