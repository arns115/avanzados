#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;cin>>n;
  vector<ll> a(n);
  for(int i =0;i<n;i++){
    cin>>a[i];
  }
  sort(a.begin(),a.end());
  if(n==1){
    if(a[0] != 1){
      cout << a[0] << " " << 1 << endl;
      return  0;
    }
    cout<<"*"<<endl;
    return 0;
  }
  if(a[0]!=1){
    cout<<a[n-1]<<" "<<1<<endl;
    return 0;
  }
  if(a[1]==(ll)sqrtl(a[1])*(ll)sqrtl(a[1])){
    cout<<a[n-1]<<" "<<(ll)sqrtl(a[1])<<endl;
    return 0;
  }
  bool d = 1;
  for(int i = 2;i<n;i++){
    if(a[i]%(a[1]*a[1])!=0){
      d=0;
      break;
    }
  }
  if(d){
    ll r = -1;
    for(int i = 2;i<n;i++){
      if(a[i]!=a[i-1]*a[1]){

        cout<< a[n-1]<<" "<<a[i-1]*a[1]<<endl;
        return 0;
      }
    }

    cout<< a[n-1]*a[1]<<" "<<a[n-1]*a[1]<<endl;
    return 0;
  }
  d=0;
  for(int i = 1;i<n-1;i++){
    if(a[n-1]%a[i]!=0){
      d=1;
      break;
    }
  }
  if(d){
    cout<<a[n-1]*a[1]<<" "<<a[n-1]*a[1]<<endl;
    return 0;
  }
  cout<<a[n-1]<<" ";
  for(int i =1;i<n-1;i++){
    auto it = lower_bound(a.begin(), a.end(), a[n - 1]/a[i]);
    if(it == a.end() || *it !=a[n -1]/a[i]){
      cout << a[n - 1]/a[i] << endl;
      return 0;
    }
  }
  cout << (ll)sqrtl(a[n - 1]) << endl;
}