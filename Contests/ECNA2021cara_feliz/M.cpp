#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int inf = 1e9;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, K; cin >> n >> m >> K;
  vector<vector<char>> a(n, vector<char>(m));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> a[i][j];
    }
  }
  vector<string> s(K);
  for(int i = 0; i < K; i++){
    cin >> s[i];
  }
  vector<vector<vector<vector<vector<int>>>>> dp(n, vector<vector<vector<vector<int>>>>(m, vector<vector<vector<int>>>(K, vector<vector<int>>(55, vector<int>(3, inf)))));
  vector<array<int, 3>> dir = {{1, 0, 0}, {0, 1 ,1}, {0, -1, 2}};
  queue<array<int, 5>> q;
  for(int i = 0; i < m; i++){
    for(int j = 0; j < K; j++){
      if(s[j][0] == a[0][i]){
        dp[0][i][j][0][0] = 1;
        q.push({0, i, j, 0, 0});
      }
    }
  }
  auto valid1 = [&](int i, int j) -> bool{
    return (i >= 0 && j >= 0 && i < n && j < m);
  };
  auto valid = [&](int i, int j, int u, int v, int d, char c) -> bool{
    return(valid1(i, j) && dp[i][j][u][v][d] == inf && c == a[i][j]);
  };
  while((int)q.size()){
    auto [i, j, u, v, dd] = q.front();
    q.pop();
    if(v == (int)s[u].length() - 1){
      for(auto [x, y, d]: dir){
        if(d + dd == 3) continue;
        if(valid1(i + x, j + y)){
          for(int k = 0; k < K; k++){
            if(a[i + x][j + y] == s[k][0]){
              char nxt = a[i + x][j + y];
              if(valid(i + x, j + y, k, 0, d, nxt)){
                dp[i + x][j + y][k][0][d] = dp[i][j][u][v][dd] + 1;
                q.push({i + x, j + y, k, 0, d});
              }
            }
          }
        }
      }
    }
    else{
      char nxt = s[u][v + 1];
      for(auto [x, y, d]: dir){
        if(d + dd == 3) continue;
        if(valid(i + x, j + y, u, v + 1, d, nxt)){
          dp[i + x][j + y][u][v + 1][d] = dp[i][j][u][v][dd] + 1;
          q.push({i + x, j + y, u, v + 1, d});
        }
      }
    }
  }
  int ans = inf;
  for(int i = 0; i < m; i++){
    for(int k = 0; k < K; k++){
      for(int l = 0; l < 3; l++){
        ans = min(ans, dp[n - 1][i][k][(int)s[k].length() - 1][l]);
      }
    }
  }
  if(ans == inf){
    cout << "impossible" << endl;
  }
  else cout << ans << endl;
}