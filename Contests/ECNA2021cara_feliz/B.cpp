#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define pb push_back
#define ll long long
#define s second
#define f first
const int MOD = 1000000007;
#define INF 1000000000000000
vector<vector<ll>> adj;
vector<ll> b;
vector<pair<ll,ll>> x;

void dfs(int a){
  x[a]={INF,INF};
  ll r=INF;
  priority_queue<int> aux;
  for(auto u:adj[a]){
    dfs(u);
    aux.push(-x[u].f);
    r=min(x[u].s,r);
  }
  if(aux.size()>=1){
    x[a].f=-aux.top()+b[a];
  }
  else{
    x[a].f=b[a];
  }
  if(aux.size()>=2){
    ll r1=0;
    r1-=aux.top();
    aux.pop();
    r1-=aux.top();
    x[a].s=min(r,r1)+b[a];
  }
  else{
    x[a].s=r+b[a];
  }
}

void solve(){
  ll n,m;cin>>n>>m;
  adj.assign(n,vector<ll>());
  x.assign(n,{-1,-1});
  b.assign(n,0);
  set<ll> st;
  for(int i=0;i<n;i++){
    st.insert(i);
  }
  for(int i=0;i<n;i++){
    cin>>b[i];
  }
  for(int i=0;i<m;i++){
    ll a,c;cin>>a>>c;
    a--;c--;
    adj[a].pb(c);
    st.erase(c);
  }
  
  priority_queue<ll> aux;
  ll pos=INF;
  for(auto u:st){
    dfs(u);
    pos=min(pos,x[u].s);
    aux.push(-x[u].f);
  }
  if(aux.size()>=2){
    ll an=0;
    an-=aux.top();
    aux.pop();
    an-=aux.top();
    pos=min(pos,an);
  }
  cout<<pos<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  // int t;cin>>t;for(int T=0;T<t;T++)
  solve();
}