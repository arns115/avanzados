#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define pb push_back
#define ll long long
#define s second
#define f first
const int MOD = 1000000007;
#define INF 10000000

map<string,vector<string>> m;
set<string> s;
string srch;
vector<string> help;
bool dfs(string a){
  s.insert(a);
  bool d=0;
  // cout<<m[a].size();
  for(int i=0;i<m[a].size();i++){
    if(s.count(m[a][i])==0){
      d=max(d,dfs(m[a][i]));
    }
  }
  // cout<<srch<<" "<<a<<endl;
  if(srch==a){
    d=1;
  }
  if(d){
    help.pb(a);
    // cout<<1<<endl;
  }
  return d;
  
}
void solve(){
  int n,q;cin>>n>>q;
  map<pair<string,string>,long double> c;
  for(int i=0;i<n;i++){
    
    int uno;cin>>uno;
    string u1;cin>>u1;
    string eq;cin>>eq;
    long double val;cin>>val;
    string u2;cin>>u2;
    
    m[u1].pb(u2);
    m[u2].pb(u1);
    c[{u1,u2}]=val;
    c[{u2,u1}]=1.0/val;
  }
  for(int i=0;i<q;i++){
    
    long double val;cin>>val;
    string u1;cin>>u1;
    string to;cin>>to;
    string u2;cin>>u2;
    
    srch=u2;
    dfs(u1);
    // for(auto u:help){
    //   cout<<u<<" ";
    // }
    // cout<<endl;
    if(help.size()==0){
      printf("impossible\n");
      continue;
    }
    reverse(help.begin(),help.end());
    long double ans=val;
    vector<long double> aux;
    for(int i=1;i<help.size();i++){
      aux.pb(c[{help[i-1],help[i]}]);
    }
    sort(aux.begin(),aux.end());
    for(int i=0;i<aux.size();i++){
      ans*=aux[i];
    }
    printf("%.20Lg\n",ans);
    help=vector<string>();
    s=set<string>();
  }
  
  
}

int main() {
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  // int t;cin>>t;for(int T=0;T<t;T++)
  solve();
}