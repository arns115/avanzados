#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ld PI = acos(-1);

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<ll> x(n), y(n);
  for(int i = 0; i < n; i++){
    cin >> x[i] >> y[i];
  }
  ld ans = 0;
  for(int i = 1; i < n - 1; i++){
    ld ss = (x[i] - x[0]) * (x[i] - x[0]) + y[i] * y[i];
    ss = sqrt(ss);
    ld sss = (x[n - 1] - x[i]) * (x[n - 1] - x[i]) + y[i] * y[i];
    sss = sqrt(sss);
    ld u = y[i] / ss;
    ld v = y[i] / sss;
    ans = max(ans, asin(u) * 180 / PI);
    ans = max(ans, asin(v) * 180 / PI);
  }
  cout << fixed << setprecision(12) << ans << endl;
}