class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        vector<int> ans(temperatures.size(),0);
        int j;
        for(int i = 0; i<temperatures.size(); ++i) {
            while(!st.empty() && temperatures[st.top()]<temperatures[i]) {
                j = st.top(); st.pop();
                ans[j] = i-j;
            }
            st.push(i);
        }
        return ans;
    }
};