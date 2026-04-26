#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> profit(2,vector<int>(n,0));
        int toggle = 0;
    
        k = min(n, k);
        if(!k) return 0;
        while(k--) {
            for (int i = 1; i < n; ++i){
                // The decision here is if
                // 1. Yesterday Price (with cut k-1) + buy yesterday and sell on today. (1 cut today)
                // 2. Yesterday Price (with cut k) + do nothing today.
                // so max of "profit till yesterday without buy/sell" vs "last with last cut (k-1) + price  diff between yesterday and today"
                profit[toggle][i] = max(profit[toggle][i-1], profit[toggle^1][i-1] + (prices[i]-prices[i-1]));
            }
            toggle ^= 1;
        }
        return profit[toggle^1][n-1];
  
    }
};


////////////// The above solution is failing for below test case:
// Input: k = 2, prices = [6,1,3,2,4,7]
int main() {
    vector<int> prices = {6,1,3,2,4,7};
    Solution sol;
    cout << sol.maxProfit(2, prices) << endl;
    return 0;
}