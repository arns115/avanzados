#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> SOS_DP(vector<ll> A, int k) {
  vector<ll> Ap = A;
  for (int i = k - 1; i >= 0; i--)
    for (int mk = 0; mk < (1 << k); mk++)
      if (mk & (1 << i))
        Ap[mk] += Ap[mk - (1 << i)];
  return Ap;
}

vector<ll> SOS_DP_inv (vector<ll> Ap, int k) {
  vector<ll> A = Ap;
  for (int i = 0; i < k; i++)
    for (int mk = 0; mk < (1 << k); mk++)
        if (mk & (1 << i)) 
            A[mk] -= A[mk - (1 << i)];
  return A;
}


int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  vector<ll> a(1 << k, 0);
  for(int i = 0; i < n; i++){
    string s; cin >> s;
    reverse(s.begin(), s.end());
    int u = 0;
    for(int j = 0; j < k; j++){
      if(s[j] == '1') u |= (1 << j);
    }
    a[u]++;
  }
  vector<ll> b = SOS_DP(a, k);
  vector<ll> c(1 << k);
  for(int i = 0; i < (1 << k); i++){
    c[i] = b[i] * b[i];
  }
  c = SOS_DP_inv(c, k);
  for(int i = 0; i < (1 << k); i++){
    c[i] -= a[i] * a[i];
    c[i] /= 2;
    c[i] += (a[i] * (a[i] - 1)) / 2;
  }
  vector<ll> d = SOS_DP(c, k);
  vector<ll> e(1 << k);
  for(int i = 0; i < (1 << k); i++){
    e[i] = d[i] * b[i];
  }
  e = SOS_DP_inv(e, k);
  for(int i = 0; i < (1 << k); i++){
    e[i] -= c[i] * 2;
    e[i] /= 3;    
  }
  int q; cin >> q;
  while(q--){
    string s; cin >> s;
    reverse(s.begin(), s.end());
    int u = 0;
    for(int j = 0; j < k; j++){
      if(s[j] == '1') u |= (1 << j);
    }
    cout << e[u] << endl;
  }

}
