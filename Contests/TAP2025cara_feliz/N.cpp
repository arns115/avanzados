#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int inf = 1e9;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  int mn = inf, mn1= inf, mx = -inf, mx1 = -inf;
  for(int i = 0; i < n; i++){
    int x, y; cin >> x >> y;
    mn = min(mn, x);
    mn1 = min(mn1, y);
    mx = max(mx, x);
    mx1 = max(mx1, y);
  }
  mn--; mn1--; mx++; mx1++;
  cout << 2 * (mx1 - mn1) + 2 * (mx - mn) << endl;
}