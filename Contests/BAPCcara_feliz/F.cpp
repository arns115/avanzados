#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

map<string, ld> mp;

ld calc(string s){
  if(mp.count(s)) return mp[s];
  int n = (int)s.length();
  string ss = s.substr(n - 2, 2);
  ld cur = mp[ss];
  ld c = 22.5;
  for(int i = n - 3; i >= 0; i--){
    if(ss == "NE"){
      if(s[i] == 'N'){
        cur += c;
      }
      else{
        cur -= c;
      }
    }
    if(ss == "NW"){
      if(s[i] == 'N'){
        cur -= c;
      }
      else{
        cur += c;
      }
    }
    if(ss == "SW"){
      if(s[i] == 'S'){
        cur += c;
      }
      else{
        cur -= c;
      }
    }
    if(ss == "SE"){
      if(s[i] == 'S'){
        cur -= c;
      }
      else{
        cur += c;
      }
    }
    c /= 2;
  }
  return cur;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string a, b; cin >> a >> b;
  mp["N"] = 90;
  mp["E"] = 0;
  mp["W"] = 180;
  mp["S"] = 270;
  mp["NE"] = 45;
  mp["NW"] = 135;
  mp["SW"] = 225;
  mp["SE"] = 315;
  ld A = calc(a), B = calc(b);
  ld ans = abs(A - B);
  A += 360;
  ans = min(ans, abs(A - B));
  cout << fixed << setprecision(12) << ans << endl;
}