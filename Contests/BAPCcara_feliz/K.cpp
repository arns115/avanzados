#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int inf = 1e9;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> a[i][j];
    }
  }
  vector<vector<vector<vector<int>>>> aa(n, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m, inf))));
  vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  auto valid1 = [&](int i, int j) -> bool{
    return(i >= 0 && j >= 0 && i < n && j < m);
  };
  auto valid = [&](int i, int j, int ii, int jj, int iii, int jjj) -> bool{
    if(valid1(i, j) == 0) return 0;
    int d = 1;
    for(auto [x, y]: dir){
      if(valid1(i + x, j + y)){
        if(abs(a[ii][jj] - a[i + x][j + y]) < abs(a[ii][jj] - a[iii][jjj]) || ((abs(a[ii][jj] - a[i + x][j + y]) == abs(a[ii][jj] - a[iii][jjj])) && abs(a[iii][jjj] - a[i][j]) > abs(a[i][j] - a[i + x][j + y]))){
          d = 0;
        }
      }
    }
    return(d && aa[i][j][ii][jj] == inf);
  };
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      aa[i][j][i][j] = 0;
      queue<pair<int, int>> q;
      q.push({i, j});
      while((int)q.size()){
        auto [x, y] = q.front();
        q.pop();
        for(auto [xx, yy]: dir){
          if(valid(x + xx, y + yy, i, j, x, y)){
            aa[x + xx][y + yy][i][j] = aa[x][y][i][j] + 1;
            q.push({x + xx, y + yy});
          }
        }
      }
    }
  }
  int mn = inf, sx;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      int cur = 0;
      for(int k = 0; k < n; k++){
        for(int l = 0; l < m; l++){
          cur = max(cur, aa[i][j][k][l]);
        }
      }
      if(mn > cur){
        mn = cur;
        sx = a[i][j];
      }
    }
  }
  if(mn == inf){
    cout << "impossible" << endl;
  }
  else{
    cout << sx << " " << mn << endl;
  }
}