class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<uint32_t, uint32_t> mp;
        for(int i = 0; i <nums.size(); ++i) mp[nums[i]]++;

        priority_queue<pair<uint32_t, uint32_t>> pq;
        for(auto it: mp) {
            pq.push({it.second,it.first});
        }
        vector<int> ans;
        while(k--) {
            ans.push_back(pq.top().second); pq.pop();
        }
        return ans;
    }
};