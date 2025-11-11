#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

const int mod = 998244353;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll n,k;cin>>n>>k;
    vector<vector<ll>> v(k+1,vector<ll>(k+1,0));
    for(int i = 1;i<=k;i++){
        v[1][i] = i;
    }
    for(ll i = 2;i<=k;i++){
        ll l = 0,r = 1;
        for(ll j = 1;j<=k;j++){
            while((l+1)*(i-1)+k<i*j){
                l++;
            }
            while((r+1)*(i-1)<j*i&&r<k){
                r++;
            }
            v[i][j] = v[i-1][r]-v[i-1][l];
            v[i][j] += mod;
            v[i][j] %= mod;
            v[i][j]+=v[i][j-1];
            v[i][j] %= mod;

        }
    }
    cout<<v[min(k,n)][k]<<endl;
}