#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

int main(){
    ll n, k; cin >> n >> k;
    vector<array<ll, 2>> a(n);
    ll mn_x = 1e9, mx_x = -1e9, mn_y = 1e9, mx_y = -1e9;
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1];
        mn_x = min(mn_x, a[i][0]);
        mn_y = min(mn_y, a[i][1]);
        mx_x = max(mx_x, a[i][0]);
        mx_y = max(mx_y, a[i][1]);
    }
    if(n == 1){
        cout << 1 << endl;
        return 0;
    }
    auto calc = [&](ll x, ll y, ll u, ll v, ll zzz, ll ccc) ->ll {
        x = min(x, zzz);
        y = min(y, ccc);
        u = max(u, zzz);
        v = max(v, ccc);
        ll xx = abs(x - u) + 1;
        ll yy = abs(y - v) + 1;
        return (xx * yy);
    }; 
    ll ans = 0; 
    vector<pair<ll, ll>> dir = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for(int i = 0; i < n; i++){
        for(auto [x, y]: dir){
            ans = max(ans, calc(mn_x, mn_y, mx_x, mx_y, a[i][0] + x * k, a[i][1] + y * k));
        }
    }
    for(int i = 0; i < k; i++){
        ans = max(ans, calc(mn_x, mn_y, mx_x + i, mx_y + k - i, a[0][0], a[0][1]));
    }
    cout << ans << endl;
}