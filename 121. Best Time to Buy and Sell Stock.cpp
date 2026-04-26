class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = INT_MAX, profit=0;
        for(int i = 0; i < prices.size();++i) {
            buy = buy > prices[i]? prices[i]: buy;
            profit = (prices[i]-buy)>profit?(prices[i]-buy):profit;
        }
        return profit;
    }
};

/*
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        int minleft = prices[0], profit = 0;
        for(int a: prices)
        {
            minleft = min(minleft, a);
            profit = max(a-minleft, profit);
        }
        return profit;
        
    }
};
*/