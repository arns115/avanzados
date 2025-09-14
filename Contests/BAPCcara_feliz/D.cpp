#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  int n; cin >> n;
  auto ask = [&](int l, int r) -> bool{
    cout << "? " << l << " " << r << endl;
    string s; cin >> s;
    return (s == "present");
  };
  auto anss = [&](int ans) -> void{
    cout << "! " << ans << endl;
  };
  int l = 0, ans = 0;
  for(int i = 0; i < n; i++){
    bool d = ask(l, i + 1);
    if(d == 0){
      ans++;
      l = i + 1;
    }
  }
  anss(ans);
}