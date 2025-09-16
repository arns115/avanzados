#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

typedef long long ll;

const int MAXN=100005;
const int inf = 1e9;

vector<int> adj[MAXN];
vector<bool> is_removed(MAXN, false);
vector<int> subtree_size(MAXN, 0);
vector<int> dis(MAXN, inf);
vector<vector<pair<int, int>>> ancestor(MAXN);
 
int get_subtree_size(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		subtree_size[node] += get_subtree_size(child, node);
	}
	return subtree_size[node];
}
 
int get_centroid(int node, int tree_size, int parent = -1) {
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		if (subtree_size[child] * 2 > tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}
 
void getDist(int cur, int centroid, int p=-1, int dist=1){
    for (int child:adj[cur]){
        if(child==p ||is_removed[child])
            continue;
        dist++;
        getDist(child, centroid, cur, dist);
        dist--;
    }
    ancestor[cur].push_back(make_pair(centroid, dist));
}
 
void update(int cur){
    for (int i=0;i<ancestor[cur].size();i++){
        dis[ancestor[cur][i].first]=min(dis[ancestor[cur][i].first], ancestor[cur][i].second);
    }
    dis[cur]=0;
}
 
int query(int cur){
    int mini=dis[cur];
    for (int i=0;i<ancestor[cur].size();i++){
       mini=min(mini, ancestor[cur][i].second+dis[ancestor[cur][i].first]);
    }
    return mini;
}
 
void build_centroid_decomp(int node = 0) {
	int centroid = get_centroid(node, get_subtree_size(node));
	
	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		getDist(child, centroid, centroid);
	}
 
	is_removed[centroid] = true;
 
	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> a(n), cnt(n);
  vector<vector<int>> who(n);
  for(int i = 0; i < n; i++){
    cin >> a[i];
    a[i]--;
    cnt[a[i]]++;
    who[a[i]].push_back(i);
  }
  for(int i = 0; i < n - 1; i++){
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int sq = sqrt(n);
  build_centroid_decomp();
  int q; cin >> q;
  vector<vector<array<int, 2>>> queries(n);
  vector<int> ans(q);
  for(int qq = 0; qq < q; qq++){
    int u, v; cin >> u >> v;
    u--; v--;
    u = a[u];
    v = a[v];
    if(cnt[u] < cnt[v]) swap(u, v);
    queries[u].push_back({v, qq});
  }
  for(int ii = 0; ii < n; ii++){
    if(queries[ii].size() == 0) continue;
    if(cnt[ii] >= sq){
      queue<int> q;
      vector<int> dist(n, inf), dist1(n, inf);
      for(int x: who[ii]){
        dist[x] = dist1[ii] = 0;
        q.push(x);
      }
      while((int)q.size()){
        int cur = q.front();
        q.pop();
        for(int x: adj[cur]){
          if(dist[x] != inf) continue;
          dist[x] = dist[cur] + 1;
          dist1[a[x]] = min(dist1[a[x]], dist[x]);
          q.push(x);
        }
      }
      for(auto [x, y]: queries[ii]){
        ans[y] = dist1[x];
      }
    }
    else{
      for(int x: who[ii]){
        update(x);
      }
      for(auto [x, y]: queries[ii]){
        int mn = inf;
        for(int u: who[x]){
          mn = min(mn, query(u));
        }
        ans[y] = mn;
      }
      for(int x: who[ii]){
        for(int i = 0; i < (int)ancestor[x].size(); i++){
          dis[ancestor[x][i].first] = inf;
        }
        dis[x] = inf;
      }
    }
  }
  for(int x: ans) cout << x << endl;
}
