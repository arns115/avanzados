#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ll n, K, x; cin >> n >> K >> x;
  vector<ll> a(n);
  ld s = 0;
  for(int i = 0; i < n; i++){
    cin >> a[i];
    s += a[i];
  }
  sort(a.begin(), a.end());
  ld ans = abs(s / n - x);
  for(int i = 0; i < n; i++){
    s -= a[i];
    ans = min(ans, abs(s / (n - 1) - x));
    s += a[i];
  }
  if(K > 1){
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        s -= a[i];
        s -= a[j];
        ans = min(ans, abs(s / (n - 2) - x));
        s += a[i];
        s += a[j];
      }
    }
  }
  if(K > 2 && n > 2){
    x *= (n - 3);
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        s -= a[i];
        s -= a[j];
        int ind = lower_bound(a.begin(), a.end(), s - x) - a.begin();
        for(int k = max(ind - 100, 0); k < min((int)n, ind + 100); k++){
          if(k == i || k == j) continue;
          s -= a[k];
          ans = min(ans, abs(s / (n - 3) - (x / (n - 3))));
          s += a[k];
        }
        s += a[i];
        s += a[j];
      }
    }
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        s -= a[i];
        s -= a[j];
        int ind = lower_bound(a.begin(), a.end(), x - s) - a.begin();
        for(int k = max(ind - 100, 0); k < min((int)n, ind + 100); k++){
          if(k == i || k == j) continue;
          s -= a[k];
          ans = min(ans, abs(s / (n - 3) - (x / (n - 3))));
          s += a[k];
        }
        s += a[i];
        s += a[j];
      }
    }
    x /= (n - 3);
  }
  if(K > 3 && n > 3){
    x *= (n - 4);
    vector<array<ll, 3>> b;
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        b.push_back({a[i] + a[j], i, j});
      }
    }
    sort(b.begin(), b.end());
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        s -= a[i];
        s -= a[j];
        int ind = lower_bound(b.begin(), b.end(), array<ll, 3>{s - x, -1, -1}) - b.begin();
        int cnt = 0;
        for(int k = ind; k >= 0; k--){
          if(b[k][1] == i || b[k][2] == j || b[k][1] == j || b[k][2] == i) continue;
          s -= b[k][0];
          ans = min(ans, abs(s / (n - 4) - (x / (n - 4))));
          s += b[k][0];
          cnt++;
          if(cnt == 5) break;
        }
        cnt = 0;
        for(int k = ind; k < (int)b.size(); k++){
          if(b[k][1] == i || b[k][2] == j || b[k][1] == j || b[k][2] == i) continue;
          s -= b[k][0];
          ans = min(ans, abs(s / (n - 4) - (x / (n - 4))));
          s += b[k][0];
          cnt++;
          if(cnt == 5) break;
        }
        s += a[i];
        s += a[j];
      }
    }
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        s -= a[i];
        s -= a[j];
        int ind = lower_bound(b.begin(), b.end(), array<ll, 3>{x - s, -1, -1}) - b.begin();
        int cnt = 0;
        for(int k = ind; k >= 0; k--){
          if(b[k][1] == i || b[k][2] == j || b[k][1] == j || b[k][2] == i) continue;
          s -= b[k][0];
          ans = min(ans, abs(s / (n - 4) - (x / (n - 4))));
          s += b[k][0];
          cnt++;
          if(cnt == 5) break;
        }
        for(int k = ind; k < (int)b.size(); k++){
          if(b[k][1] == i || b[k][2] == j || b[k][1] == j || b[k][2] == i) continue;
          s -= b[k][0];
          ans = min(ans, abs(s / (n - 4) - (x / (n - 4))));
          s += b[k][0];
          cnt++;
          if(cnt == 5) break;
        }
        s += a[i];
        s += a[j];
      }
    }
  }
  cout << fixed << setprecision(12) << ans << endl;
}