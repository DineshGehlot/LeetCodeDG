#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> product(nums.size());
        product[0] = nums[0];
        int rightMax = 1;
        for (int i = 1; i < nums.size(); ++i)
            product[i] = product[i-1]*nums[i];
        for (int i = nums.size()-1; i>0; --i) {
            product[i] = product[i-1]*rightMax;
            rightMax *= nums[i];
        }
        product[0] = rightMax;
        return product;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,2,3,4};
    vector<int> result = s.productExceptSelf(nums);
    for (int i = 0; i < nums.size(); ++i)
        cout << result[i] << " ";
    return 0;
}