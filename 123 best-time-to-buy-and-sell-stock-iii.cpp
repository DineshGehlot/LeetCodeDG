#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> leftProfit(prices.size());
        int buy = prices[0], sell = prices[prices.size()-1], rightProfit = 0, profit = 0 ;
        leftProfit[0] = 0;
        for(int i = 1; i< prices.size(); ++i) {
            buy = min(buy, prices[i]);
            leftProfit[i] = max(leftProfit[i-1],prices[i]-buy);
        }
        for (int i =prices.size()-1;i>0; --i) {
            sell = max(sell, prices[i]);
            rightProfit = max(sell-prices[i],rightProfit);
            profit = max(rightProfit+leftProfit[i], profit);
        }
        return profit;
    }
};