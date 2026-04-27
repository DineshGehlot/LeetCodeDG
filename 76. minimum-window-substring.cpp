#include <string>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> dict(256,0), curr(256,0);
        int i, count = 0,tCount=t.size(), retInd=-1, retSize=INT_MAX;
        for (i = 0; i < t.size(); ++i) {
            ++dict[t[i]];
        }
        i = 0;
        for(int j =0; j<s.size(); ++j) {
            ++curr[s[j]];
            if (curr[s[j]] <= dict[s[j]]) ++count;

            while (count == tCount) {
                if (retSize > j - i + 1) {
                    retInd = i;
                    retSize = j - i + 1;
                }
                --curr[s[i]];
                if (curr[s[i]] < dict[s[i]]) --count;
                ++i;
            }
        }
        if (retInd == -1) return "";
        return s.substr(retInd, retSize);
    }
};

int main() {
    Solution sol;
    string result = sol.minWindow("a", "aa");
    cout << result << endl;
    return 0;
}