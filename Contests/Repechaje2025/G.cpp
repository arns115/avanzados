#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int inf = 1e9;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  string t; cin >> t;
  t = string(8, '0') + t + string(8, '0');
  n = (int)t.size();
  int m = 256;
  vector<int> ans(m, n + 1);
  vector<int> a(n);
  for(int i = 0; i < n; i++){
    a[i] = (t[i] == '1');
  } 
  int xx = (1 << 8) - 1;
  for(int ii = 0; ii < m; ii++){
    vector<vector<int>> dp(n, vector<int>(m, inf));
    fill(dp[7].begin(), dp[7].end(), 0);
    for(int i = 8; i < n; i++){
      for(int j = 0; j < m; j++){
        if(a[i - 8] == (j >> 7)){
          dp[i][((j << 1) & xx)] = min(dp[i][((j << 1) & xx)], dp[i - 1][j]);
          dp[i][((j << 1) & xx) ^ ii] = min(dp[i][((j << 1) & xx) ^ ii], dp[i - 1][j] + 1);
        }
      }
    }
    ans[ii] = *min_element(dp[n - 1].begin(), dp[n - 1].end());
  }
  int mn = n + 5, who = 0;
  for(int i = 0; i < m; i++){
    if(ans[i] < mn){
      mn = ans[i];
      who = i;
    }
  }
  for(int i = 7; i >= 0; i--){
    cout << ((who & (1 << i)) ? "1" : "0");
  }
  cout << " " << mn << endl;
}
