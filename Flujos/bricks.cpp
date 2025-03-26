#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

#define all(v) v.begin(),v.end()
#define pb(x) push_back(x)

const ll inf = 1e17;

struct flowEdge {
    int u,v;
    ll cap,flow = 0; 
    flowEdge(int u, int v, ll cap) : u(u), v(v), cap(cap) {};
};

struct Dinic{
    vector<flowEdge> edges; 
    vector<vi> adj; 
    int n,s,t; 
    int id = 0;
    vi level, next; 
    
    queue<int> q;
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        next.resize(n);
        fill(all(level),-1); 
        level[s] = 0; 
        q.push(s);
    }

    void add(int u, int v, ll cap){
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0);
        adj[u].pb(id++); 
        adj[v].pb(id++); 
    }

    bool bfs(){
        while (!q.empty()){
            int curr = q.front();
            q.pop();
            for (auto e : adj[curr]){
                if (edges[e].cap - edges[e].flow  < 1) continue; 
                if (level[edges[e].v] != -1) continue; 
                level[edges[e].v] = level[edges[e].u] + 1; 
                q.push(edges[e].v);
            }
        }
        return level[t] != -1; 
    }

    ll dfs(int u, ll flow){
        if (flow == 0) return 0;
        if (u == t) return flow;
        for (auto& cid = next[u]; cid < adj[u].size(); cid++){ 
            int e = adj[u][cid]; 
            int v = edges[e].v; 

            if (level[edges[e].u] + 1 != level[v] || edges[e].cap - edges[e].flow < 1) continue;
            ll f = dfs(v,min(flow,edges[e].cap - edges[e].flow)); 
            if (f == 0) continue; 
            edges[e].flow += f; 
            edges[e ^ 1].flow -= f;
            return f;
        }
        return 0;
    }

    ll maxFlow(){
        ll flow = 0;
        while (bfs()){
            fill(all(next),0);
            for (ll f = dfs(s,inf); f != 0ll; f = dfs(s,inf)) flow += f;
            fill(all(level),-1); 
            level[s] = 0;
            q.push(s);
        }
        return flow;
    }

};

const ll MAX = 202;
char grid[MAX][MAX];

bool areAdj(pair<ll,ll> &a, pair<ll,ll> &b){
    return a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    ll n,m; cin >> n >> m;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            cin >> grid[i][j];
    vector<pair<ll,ll>> a,b;
    ll cnt = 0;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if(grid[i][j] != '#')
                continue;
            cnt++;
            if(i != n-1 && grid[i+1][j] == '#'){
                a.emplace_back(i*m+j,(i+1)*m+j);
            }
            if(j != m-1 && grid[i][j+1] == '#'){
                b.emplace_back(i*m+j,i*m+j+1);
            }
        }
    }
    ll as = a.size(), bs = b.size();
    Dinic flow(as+bs+2, as+bs, as+bs+1);
    for(int i = 0 ; i < as ; i++)
        flow.add(as+bs,i,1);
    for(int i = 0 ; i < bs ; i++)
        flow.add(as+i,as+bs+1,1);
    for(int i = 0 ; i < as ; i++)
        for(int j = 0 ; j < bs ; j++)
            if(areAdj(a[i], b[j]))
                flow.add(i, as+j, 1);
    ll ma = flow.maxFlow();
    ll ans = cnt - (as + bs - ma);
    cout << ans << '\n';
}
