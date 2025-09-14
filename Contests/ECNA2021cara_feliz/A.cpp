#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> dp(n + 1, n + 1);
  dp[0] = 0;
  dp[1] = 1;
  for(int i = 2; i <= n; i++){
    int &r = dp[i];
    for(int j = 1; j < i; j++){
      r = min(r, dp[j] + dp[i - j]);
    }
    for(int j = 2; j * j <= i; j++){
      if(i % j == 0){
        r = min(r, dp[j] + dp[i / j]);
      }
    }
    string t = to_string(i);
    int sz = (int)t.length();
    for(int s = 1; s < (1 << sz); s++){
      int c = 0, last = 0;
      for(int i = 0; i < sz; i++){
        if(s & (1 << i)){
          if(stoi(t.substr(last, i - last + 1)) == 0 || t[last] == '0'){
            c = n + 1;
            break;
          }
          c +=dp[stoi(t.substr(last, i - last + 1))];
          last = i + 1;
        }
      }
      if(last != sz){
        if(stoi(t.substr(last, sz - last)) == 0|| t[last] == '0'){
          continue;
        }
        c +=  dp[stoi(t.substr(last, sz - last))];
      }
      r = min(r, c);
    }
  }
  cout << dp[n] << endl;
}