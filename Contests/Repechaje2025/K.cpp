#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1e9+7;

ll binpow(ll a, ll b){
    ll r=1;
    while(b){
        if(b%2LL)
            r=(r*a)%MOD;
        a=(a*a)%MOD;
        b/=2;
    }
    return r;
}

int main(){
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  ll a,b;cin>>a>>b;
  a--;b--;
  ll mx = 0;
  for(ll i = 0;i<200;i++){
    for(ll j = 0; j<200;j++){
      ll aux = 0;
      if(a<i)continue;
      if(b<j)continue;
      aux+=__builtin_popcountll(a-i+b-j);
      aux+=a-i-__builtin_popcountll(a-i);
      aux+=b-j-__builtin_popcountll(b-j);
      mx=max(mx,aux);
    }
  }
  cout<<binpow(2,mx+1)<<endl;
}
