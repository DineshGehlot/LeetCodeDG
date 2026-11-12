class Solution {
public:
    int findComplement(int num) {
        unsigned int MASK = 1U, temp = num;
        while (temp) {
            temp = temp >>1;
            MASK = MASK <<1;
        }
        return num ^ (MASK-1);
    }
};
