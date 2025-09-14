#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dp[100005][700];

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, X; cin >> n >> X;
  vector<ll> a(n + 1, 0), pre(n + 1, 0);
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    pre[i] = pre[i - 1] + a[i];
  }
  int sq = sqrt(2 * n) + 5;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j < sq; j++){
      if(j <= i) dp[i][j] = max(dp[i - 1][j], dp[i - j][j - 1] - (pre[i] - pre[i - j]) + X);
    }
  }
  ll ans = 0;
  for(int i = 0; i <= n; i++){
    for(int j = 0; j < sq; j++){
      ans = max(ans, dp[i][j]);
    }
  }
  cout << ans << endl;
}