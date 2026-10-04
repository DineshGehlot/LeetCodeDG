class Solution {
public:
    int reverseBits(int n) {
        unsigned int left = 1 << 31, right  = 1;
        while(left > right) {
            if (( (n & left) > 0) != ((n & right) > 0)) {
                // if both different then toggle
                n = n ^ (left | right);
            }
            left = left >> 1;
            right = right << 1;
        
        }
        return n;
    }
};

// Can also be done
/*
result = 0;
for (int i = 0; i < 32; i++) {
    result = result << 1; // shift left to make room for the next bit
    result = result | (n & 1); // add the least significant bit of n
    n = n >> 1; // shift n right to process the next bit
}
return result;
*/