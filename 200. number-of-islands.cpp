class Solution {
    int m,n;
    void floodfill(vector<vector<char>>& grid, int i, int j) {
        if(i<0 || i>=m || j<0 || j>=n) return;
        if('0'==grid[i][j]) return;
        grid[i][j] = '0';
        floodfill(grid,i, j+1);
        floodfill(grid,i, j-1);
        floodfill(grid,i+1, j);
        floodfill(grid,i-1, j);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int count = 0;
        for(int i = 0; i<m; ++i) {
            for (int j =0; j<n; ++j) {
                if(grid[i][j]=='1') {
                    ++count;
                    floodfill(grid,i,j);
                }
            }
        }
        return count;
    }
};