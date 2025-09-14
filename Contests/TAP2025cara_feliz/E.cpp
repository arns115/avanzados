#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=200005;
vector<int> adj[N];
vector<int> start(N), end1(N), depth(N);
vector<ll> b(N, 0), a(N);
vector<vector<ll>> dd(N);
vector<vector<int>> t(N, vector<int>(32));
int timer=0, sz = 0;
int n, l = (int)ceil(log2(N));
 

void dfs(int cur, int p, int cnt){
  sz++;
    depth[cur]=cnt;
    b[cnt] += a[cur];
    if(a[cur] != 0) dd[cnt].push_back(cur);
    t[cur][0]=p;
    start[cur]=timer++;
    for(int i=1;i<=l;i++){
        t[cur][i]=t[t[cur][i-1]][i-1];
    }
    for(int x:adj[cur]){
        if(x==p) continue;
        dfs(x, cur, cnt+1);
    }
    end1[cur]=++timer;
}
 
bool ancestor(int u, int v){
    return start[u]<=start[v] && end1[u]>=end1[v];
}
 
int lca(int u, int v){
    if(ancestor(u, v))
        return u;
    if (ancestor(v, u)){
        return v;
    }
    for(int i=l;i>=0;i--){
        if(!ancestor(t[u][i], v)){
            u=t[u][i];
        }
    }
    return t[u][0];
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  for(int i = 2; i <= n; i++){
    cin >> a[i];
  }
  vector<int> c;
  for(int i = 0; i < n - 1; i++){
    int u, v; cin >> u >> v;
    if(u == 1){
      c.push_back(v);
      continue;
    }
    else if (v == 1){
      c.push_back(u);
      continue;
    }
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  ll ans = 0, tt = 1000000000;
  for(int x: c){
    sz = 0;
    dfs(x, x, 0);
    for(int i = 0; i < sz; i++){
      if(dd[i].size() == 0) continue;
      int v = dd[i][0];
      for(int u = 1; u < (int)dd[i].size(); u++){
        v =lca(v, dd[i][u]);
      }
      if(ans < b[i]){
        ans = b[i];
        tt = i - depth[v] + 1;
      }
      if(ans == b[i]){
        tt = min(tt, 1LL * i - depth[v] + 1);
      }
    }
    for(int i = 0; i < sz; i++){
      dd[i].clear();
      b[i] = 0;
    }
  }
  cout << ans << " " << tt << endl;
}