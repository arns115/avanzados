#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define pb push_back
#define ll long long
#define s second
#define f first
const int MOD = 1000000007;
#define INF 10e18

void solve(){
  int c,t,r;cin>>c>>t>>r;
  double p;cin>>p;
  vector<vector<long double>> e(c+1,vector<long double>(c+1));
  e[0][0]=0;
  vector<long double> best(c+1,INF);
  for(int i=0;i<=c;i++){
    if(i!=0){
      e[i][i]=best[i]+t;
    }
    for(int j=i+1;j<=c;j++){
      if(i!=0){
        e[i][j]=e[i][j-1]+1+p*r+p*e[0][j-i];
      }
      else{
        e[i][j]=(e[i][j-1]+1+p*r)/(1-p);
      }
      best[j]=min(best[j],e[i][j]);
      // cout<<e[i][j]<<" ";
    }
    // cout<<endl;
  }
  cout<<fixed<<setprecision(10);
  cout<<e[c][c]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  // int t;cin>>t;for(int T=0;T<t;T++)
  solve();
}