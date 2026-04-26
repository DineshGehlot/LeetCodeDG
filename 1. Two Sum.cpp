using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> myMap;
        for(int i =0; i< nums.size(); ++i) {
            if(myMap.find(nums[i])!= myMap.end())
                return {i,myMap[nums[i]]};
             myMap[(target-nums[i])] = i;
        }
        return {};
    }
};

/*
O(nlogn)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        
        vector<pair<int,int>> vii;
        for(int i=0; i<nums.size();++i)
        {
            vii.emplace_back(nums[i],i);
        }
        sort(vii.begin(),vii.end());
        vector<int> ans(2);
        int i = 0, j = nums.size()-1;
        while(i<j)
        {
            if(vii[i].first+vii[j].first==target)
            {
                ans[0] =vii[i].second;
                ans[1] =vii[j].second;
                return ans;
            }
            else if(vii[i].first+vii[j].first<target) ++i;
            else --j;
        }
        return ans;
    }
};
*/