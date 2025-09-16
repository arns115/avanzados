#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 998244353;
template<int MOD>
struct ModInt {
  ll v;
  ModInt(ll _v = 0) {v = (-MOD < _v && _v < MOD) ? _v : _v % MOD; if (v < 0) v += MOD;}
  ModInt& operator += (const ModInt &other) {v += other.v; if (v >= MOD) v -= MOD; return *this;}
  ModInt& operator -= (const ModInt &other) {v -= other.v; if (v < 0) v += MOD; return *this;}
  ModInt& operator *= (const ModInt &other) {v = v * other.v % MOD; return *this;}
  ModInt& operator /= (const ModInt &other) {return *this *= inverse(other);}
  bool operator == (const ModInt &other) const {return v == other.v;}
  bool operator != (const ModInt &other) const {return v != other.v;}
  friend ModInt operator + (ModInt a, const ModInt &b) {return a += b;}
  friend ModInt operator - (ModInt a, const ModInt &b) {return a -= b;}
  friend ModInt operator * (ModInt a, const ModInt &b) {return a *= b;}
  friend ModInt operator / (ModInt a, const ModInt &b) {return a /= b;}
  friend ModInt operator - (const ModInt &a) {return 0 - a;}
  friend ModInt power(ModInt a, ll b) {ModInt ret(1); while (b > 0) {if (b & 1) ret *= a; a *= a; b >>= 1;} return ret;}
  friend ModInt inverse(ModInt a) {return power(a, MOD - 2);}
  friend istream& operator >> (istream &is, ModInt &m) {is >> m.v; m.v = (-MOD < m.v && m.v < MOD) ? m.v : m.v % MOD; if (m.v < 0) m.v += MOD; return is;}
  friend ostream& operator << (ostream &os, const ModInt &m) {return os << m.v;}
};

const int maxn = 4005;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> adj(n);
  for(int i = 0; i < m; i++){
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<ModInt<mod>> fact(maxn, 1), inv(maxn, 1);
  for(int i = 2; i < maxn; i++){
    fact[i] = fact[i - 1] * i;
  }
  inv[maxn - 1] = power(fact[maxn - 1], mod - 2);
  for(int i = maxn - 1; i; i--){
    inv[i - 1] = inv[i] * i;
  }
  vector<vector<ModInt<mod>>> cnt(maxn, vector<ModInt<mod>>(maxn / 2, 0));
  vector<vector<ModInt<mod>>> pre(maxn, vector<ModInt<mod>>(maxn / 2, 0));
  cnt[0][0] = 1;
  for(int i = 0; i < maxn; i++){
    pre[i][0] = 1;
  }
  for(int i = 1; i < maxn; i++){
    for(int j = 1; j < maxn / 2; j++){
      if(j > i) continue;
      cnt[i][j] = pre[i - 1][j - 1] - (k < i ? pre[i - k - 1][j - 1] : 0);
    }
    for(int j = 1; j < maxn / 2; j++){
      pre[i][j] = pre[i - 1][j] + cnt[i][j];
    }
  }
  ModInt<mod> ans = 0;
  vector<ModInt<mod>> dp(n, 0), dp1(n, 0);
  dp[0] = 1;
  int mn = maxn;
  for(int ii = 1; ii < maxn; ii++){
    if((ii + k - 1) / k > mn) break;
    for(int i = 0; i < n; i++){
      for(int x: adj[i]){
        dp1[x] += dp[i];
      }
    }
    if(dp1[1] != 0 && mn == maxn) mn = (ii + k - 1) / k;
    if(mn != maxn){
      ans += dp1[1] * cnt[ii][mn];
    }
    dp = dp1;
    fill(dp1.begin(), dp1.end(), 0);
  }
  cout << ans << endl;
}
