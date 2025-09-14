#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
  ll w, h; cin >> w >> h;
  auto ask = [&](ll x, ll y) -> bool{
    cout << "? " << x << " " << y << endl;
    string s; cin >> s;
    return (s == "building");
  };
  auto anss = [&](ll x, ll y) -> void{
    cout << "! " << x << " " << y << endl;
  };
  vector<int> a(w);
  iota(a.begin(), a.end(), 1);
  shuffle(a.begin(), a.end(), rng);
  ll mx = 0, ww = 1;
  for(int i = 0; i < w; i++){
    if(ask(a[i], min(mx + 1, h)) == 0) continue;
    ll l = mx + 1, r = h;
    while(l <= r){
      ll mid = (l + r) / 2;
      if(ask(a[i], mid)){
        mx = mid;
        ww = a[i];
        l = mid + 1;
      }
      else{
        r = mid - 1;
      }
    }
  }
  anss(ww, mx);
}