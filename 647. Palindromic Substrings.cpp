class Solution {
public:
    int countSubstrings(string s) {
        int i,j,count=0, n = s.size();

        for(int k = 0; k < n; ++k){
            i = j = k;
            while(i>=0 && j<n && s[i]==s[j]) {
                ++count;
                ++j;
                --i;
            }

            i = k;
            j = k+1;
            while(i>=0 && j<n && s[i]==s[j]) {
                ++count;
                ++j;
                --i;
            }


        }
        return count;
    }
};

/*
class Solution {
    int n;
    bool countPD(string &s, vector<vector<int>> &dp, int i, int j) {
        if(i<0 || i>=n || j <0 || j >= n ) return  false;
        if(dp[i][j] != -1) return dp[i][j];
        if(i==j ||  j<i) {
            dp[i][j] = 1;
            return true;
        }
        if(s[i]==s[j]){
            if(countPD(s,dp,i+1, j-1)){
                dp[i][j] = dp[i+1][j-1] + 1;
                return true;
            }
        }
        dp[i][j] = 0;
        return false;
    }
public:
    int countSubstrings(string s) {
        n = s.size();
        int counter = 0;
        vector<vector<int>> isPD(n, vector<int>(n,-1));
        for(int i = 0; i < n; ++i ) {
            for(int j = i; j<n; ++j) {
                if(countPD(s, isPD, i, j))
                    counter++;
            }
        }
        return counter;
    }
};
*/