class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        while (n) {
            count += (n&1);
            n = n>>1;
        }
        return count;
    }
};

// We coulld also use n & (n-1) to clear the least significant bit that is set to 1 in each iteration
