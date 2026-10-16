/*
Question: https://thejoboverflow.com/problem/332/

There are n friends, numbered from 1  to n, who buy wholesale products from different companies.
There are m pairs of friends where each pair of friends is connected by the common company they buy products from. Companies are numbered from 1 to 100.

Note that if a and b are connected by a company c, and b and d are also connected by the company c, then a and d are also connected by the company c. Find the maximal product of a and b that share the largest group of friends which is connected by a common company.

Input
The first line of input consists of 2 space separated integers − n and m  
Each of the next m lines consist of 3 space separated integers u, v and w
which denotes that the friends numbered u and v are connected by the company numbered w

Constraints:
(1≤n,m≤105)
(1≤u,v≤n)
(1≤w≤100)

Output
The output should consist of a single integer − the maximal product.

Example
Input
5 5
1 2 1
2 3 1
1 3 1
3 4 2
4 5 2

Output
20
*/

#include <bits/stdc++.h>
using namespace std;
  
  struct groupInfo {
    uint32_t size;
    uint64_t max1, max2;
  };
  
int findParent(int x, vector<int>& parent) {
    if (parent[x] != x)
        parent[x] = findParent(parent[x], parent);
    return parent[x];
}
  
vector<uint64_t> findMax(int n, vector<vector<uint32_t>> &company) {
  vector<int> parent(n);
  iota(parent.begin(), parent.end(), 0);
    uint32_t Px,Py,x,y;
    for (auto& row :company) {
      x = row[0];
      y = row[1];
      Px = findParent(x, parent);
      Py = findParent(y, parent);
      if(Px != Py) 
        parent[Px] = Py;
    }
    unordered_map<int,struct groupInfo> mp;
    for(int i = 1; i<parent.size(); ++i)
    {
      int gId = findParent(i, parent);
      mp[gId].size++;
      if(i > mp[gId].max2) {
        mp[gId].max1 = mp[gId].max2;
        mp[gId].max2 = i;
      } else if (i > mp[gId].max1) {
        mp[gId].max1 = i;
      }
    }
    
    uint32_t maxNodes =0;
    uint64_t maxProduct = 0;
    for(auto& [gId, gInfo] : mp)
    {
      if((gInfo.size> maxNodes))
      {
        maxNodes = gInfo.size;
        maxProduct = gInfo.max1 * gInfo.max2;
      } else if(gInfo.size== maxNodes)
          maxProduct = max(static_cast<uint64_t>(gInfo.max1 * gInfo.max2), maxProduct);
    }
    return {maxNodes,maxProduct};
  }

  uint64_t findMaxProduct(int n,  vector<vector<vector<uint32_t>>> &companies) {
    uint32_t MaxDepth = 0;
    uint64_t MaxProd = 0;

    for (int i = 1; i<=100;i++) {
      auto curr = findMax(n,companies[i]);
      if(MaxDepth<curr[0]) {
        MaxDepth = curr[0];
        MaxProd = curr[1];
      } if(MaxDepth == curr[0]) {
        MaxProd = max(MaxProd, curr[1]);
      }
    }
    return MaxProd;
  }

  int main() {
    uint32_t n,m;
    cin>>n>>m;
    ++n;
    vector<vector<vector<uint32_t>>> companies(101);
    
    uint32_t x, y,w;
    for (int i =0; i<m;++i) {
      cin >> x >> y >> w;
      companies[w].push_back({x,y});
    }
    cout << findMaxProduct(n, companies);

    return 0;

  }