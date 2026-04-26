#include <iostream>
#include <map>
#include <string>

using namespace std;
// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         map<char, int> mp;
//         int maxSize = 0,currSize = 0, j = 0;
//         for(int i = 0; i < s.size(); ++i) {
//             if(mp.find(s[i])!= mp.end()) {
//                 j = max(j, mp[s[i]]);
//                 currSize = i-j;
//             }
//             else
//                 currSize += 1;
//             maxSize = max(currSize, maxSize);
//             mp[s[i]] = i;
//         }
//         return maxSize;
//     }
// };

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> mp;
        int maxSize = 0,currSize = 0, j = -1;
        for(int i = 0; i < s.size(); ++i) {
            if(j<=mp[s[i]]) {
                currSize = i-j;
            } else
                currSize += 1;
            maxSize = max(currSize, maxSize);
            mp[s[i]] = i;
        }
        return maxSize;
    }
};

int main() {
    Solution s;
    string str = "abcabcbb";
    cout << s.lengthOfLongestSubstring(str);
    return 0;
}

/*
au
cdd
abba
abcabcbb
abbcca
*/