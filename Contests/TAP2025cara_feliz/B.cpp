#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 998244353;

ll binpow(ll a, ll b){
  ll r=1;
  while(b){
      if(b%2)
          r=(r*a)%mod;
      a=(a*a)%mod;
      b/=2;
  }
  return r;
}

ll divide(ll a, ll b){
  return ((a%mod)*binpow(b, mod-2))%mod;
}

ll binom(ll a, ll b){
  ll x = 1,y = 1;
  for(int i = 1;i<=b;i++){
    x*=a+1-i;
    x%=mod;
    y*=i;
    y%=mod;
  }
  return divide(x,y);
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n,k;cin>>n>>k;
  vector<ll> b(n-k+10);
  for(int i = 1;i<=n-k+1;i++){
    cin>>b[i];
  }
  vector<ll> a(k+2,0);
  vector<ll> pb(k+2,0);
  for(int i = 1;i<=k;i++){
    for(int j = 0;i+j*k+1<=n-k+1;j++){
      pb[i]+=b[i+j*k] - b[i+j*k+1];
      a[i] = max(a[i],pb[i]);
    }
  }
  ll tot = 0;
  for(int i = 1;i<=k;i++){
    tot+=a[i];
  }
  tot = b[1] - tot;
  if(tot<0){
    cout<<0<<endl;
    return 0;
  }
  cout<<binom(tot+k-1,k-1)<<endl;
}