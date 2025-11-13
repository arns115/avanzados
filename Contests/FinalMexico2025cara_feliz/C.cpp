#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool cmp(const array<ll, 4> &a, const array<ll, 4>&b){
  if(a[0] * b[1] > a[1] * b[0]){
    return false;
  }
  if(a[0] * b[1] < a[1] * b[0]){
    return true;
  }
  if(a[3] != b[3]){
    if(a[3] == 0){
      return false;
    }
    if(b[3] == 0){
      return true;
    }
  }
  return a[2] < b[2];
}

struct SegmentTree {
  vector<ll> a; 
  int n;        

  SegmentTree(int _n) : a(2 * _n, 0), n(_n) {}

  void update(int pos, ll val) {
    pos += n;      
    a[pos] = val;
    for (pos /= 2; pos > 0; pos /= 2) {
      a[pos] = a[2 * pos] + a[2 * pos + 1]; 
    }
  }

  ll get(int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res += a[l++]; 
      if (r & 1) res += a[--r]; 
    }
    return res;
  }
};

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, s, k; cin >> n >> s >> k;
  vector<array<ll, 3>> a(n);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 3; j++){
      cin >> a[i][j];
    }
  }
  sort(a.begin(), a.end());
  vector<array<ll, 4>> b;
  array<ll, 2> best = {-1, -1};
  auto fix = [&](ll x, ll y, ll i, ll ii) -> array<ll, 4>{
    ll z = gcd(x, y);
    x /= z;
    y /= z;
    return {x, y, i, ii};
  };
  auto calc = [&](ll x, ll y) -> void{
    ll z = gcd(x, y);
    x /= z;
    y /= z;
    if(best[0] == -1){
      best = {x, y};
      return;
    }
    if(best[0] * y > best[1] * x){
      best = {x, y};
      return;
    }
  };
  for(int i = 0; i < n; i++){
    b.push_back(fix(a[i][1], a[i][0], i, 1));
    b.push_back(fix(a[i][2], a[i][0], i, 0));
  }
  SegmentTree st(n), st1(n);
  sort(b.begin(), b.end(), cmp);
  for(auto [x, y, ind, start]: b){
    if(start){
      ll u = k / a[ind][0];
      st.update(ind, u);
      st1.update(ind, u * a[ind][0]);
      int l = 1, r = n, f = -1;
      while(l <= r){
        int mid = (l + r) / 2;
        if(st.get(0, mid) >= s){
          f = mid;
          r = mid - 1;
        }
        else{
          l = mid + 1;
        }
      }
      if(f != -1){
        ll cnt = st1.get(0, f);
        ll v = st.get(0, f);
        ll vv = v - s;
        cnt -= a[f - 1][0] * vv; 
        calc(cnt * x, y);
      } 
    }
    else{
      st.update(ind, 0);
      st1.update(ind, 0);
    }
  }
  if(best[0] == -1){
    cout << "*" << endl;
    return 0;
  }
  cout << best[0] << " " << best[1] << endl;
}
