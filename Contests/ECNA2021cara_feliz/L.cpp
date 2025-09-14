#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void R(vector<vector<int>>& a) {
  int n = (int)a.size(), m = (int)a[0].size();     
  vector<vector<int>> b(m, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b[j][n - i - 1] = a[i][j];
    }
  }
  a = b;
}

int calc(vector<vector<int>>& a, vector<int> b){
  int n = (int)a.size(), m = (int)a[0].size();    
  int cnt, cur;
  cnt = cur = 0;
  for(int i = 0; i < n + m - 1; i++){
    int si = max(i - m + 1, 0);
    int ei = min(i, n - 1);
    int ci = min(i, m - 1);
    vector<int> bb;
    for(int j = si; j <= ei; j++){
      if(a[j][ci] != -1) bb.push_back(a[j][ci]);
      ci--;
    }
    int sz = (int)bb.size();
    if(sz == 0) continue;
    int x = b[cnt], y = b[cnt + sz - 1];
    for(int u: bb){
      if(u < x || u > y) cur++;
    }
    cnt += sz;
  }
  return cur;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m));
  vector<int> b;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> a[i][j];
      if(a[i][j] == -1) continue;
      b.push_back(a[i][j]);
    }
  } 
  sort(b.begin(), b.end());
  int ans = n * m + 1;
  ans = min(ans, calc(a, b));
  R(a);
  ans = min(ans, calc(a, b));
  R(a);
  ans = min(ans, calc(a, b));
  R(a);
  ans = min(ans, calc(a, b));
  cout << ans << endl;
}