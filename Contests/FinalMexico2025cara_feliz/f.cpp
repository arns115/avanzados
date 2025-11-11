#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size()

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int n = sz(s);
    ll a = 0;
    for(int i = 0; i < min(n, 14); i++){
        a *= 10;
        a += (s[i] - '0');
    }
    map<ll, ll> mp;
    for(ll i = 2; i * i <= a; i++){
        while(a % i == 0){
            mp[i]++;
            a /= i;
        }
    }
    if(a > 1) mp[a]++;
    ll x = n - min(n, 14);
    if(x > 0){
        mp[2] += x;
        mp[5] += x;
    }
    cout << sz(mp) << endl;
    for(auto [xx, yy]: mp){
        cout << xx << " " << yy << endl;
    }
}