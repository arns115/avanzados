#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> a(n, 0);
  int ans = 0;
  for(int i = 0; i < m; i++){
    int x, y; cin >> x >> y;
    vector<int> b(n);
    int cnt = 0;
    for(int j = 0; j < n; j++){
      cin >> b[j];
      if(b[j] == 1) cnt++;
    }
    if(x / (cnt + 1) >= y){
      ans += x / (cnt + 1);
      for(int j = 0; j < n; j++){
        if(b[j] == 1) a[j] += x / (cnt + 1);
      }
    }
    else{
      ans += y;
      for(int j = 0; j < n; j++){
        if(b[j] == 1) a[j] += x / (cnt);
      }
    }
    for(int j = 0; j < n; j++){
      if(b[j] == 2) a[j] += y;
    }
  }
  for(int x: a){
    cout << x << " ";
  }
  cout << ans << endl;
}
