#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ll n, x; cin >> n >> x;
  ll s = 0;
  vector<ll> a(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
    s += a[i] * a[i];
  }
  if(x == 0 || s == 0){
    for(int i = 0; i < n; i++){
      cout << 0 << " ";
    }
    cout << endl;
    return 0;
  }
  ld val = x * n;
  val /= s;
  val = sqrt(val);
  for(int i = 0; i < n; i++){
    cout << fixed << setprecision(12) << val * a[i] << " ";
  }
  cout << endl;
}