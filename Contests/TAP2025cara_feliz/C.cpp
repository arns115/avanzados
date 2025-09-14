#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;cin>>n;
  vector<ll> v(n);
  vector<ll> b(n,0);
  for(int i =0;i<n;i++){
    cin>>v[i];
    b[(v[i]+i)%n]++;
  }
  ll tot = 0;
  for(int i=0;i<n;i++){
    tot+=(b[i]*(b[i]-1));
  }
  cout << tot + n << endl;
}