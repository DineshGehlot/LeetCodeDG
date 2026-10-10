class Solution {
private:
   vector<int> curr;
   vector<vector<int>> ans;
    void combSum(int steps, int sum, int i) {
        if (steps == 0 && sum == 0) {
            ans.push_back(curr);
            return;
        }
        if (steps <= 0 || sum <= 0 || i > 9) return;

        curr.push_back(i);
        combSum(steps-1, sum-i, i+1);
        curr.pop_back();
        combSum(steps,sum, i+1);
    } 
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if(n > 45) return ans;
        combSum(k,n,1);
        return ans;

    }
};