// Racso programmed here
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128 sll;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<pll> vpll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(a) (int)(a.size())
#define fori(i,a,n) for(int i = a; i < n; i++)
#define endl '\n'
const int MOD = 1e9+7;
const ll INF = 1e17;
const long long LLINF = LLONG_MAX;
const double EPS = DBL_EPSILON;
void fastIO() { ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

// Same implementation shown in 'flowCommented', but without comments.
struct flowEdge
{
    int u, v;
    ll cap, flow = 0;
    flowEdge( int u, int v, ll cap ) : u(u), v(v), cap(cap) {};
};

struct Dinic
{
    vector<flowEdge> edges;
    vector<vi> adj;
    int n, s, t, id = 0;
    vi level, next;
    queue<int> q;

    Dinic( int n, int s, int t ) : n(n), s(s), t(t)
    {
        adj.resize(n);
        level.resize(n);
        next.resize(n);
        fill(all(level),-1);
        level[s] = 0;
        q.push(s);
    }

    void addEdge( int u, int v, ll cap )
    {
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0);
        adj[u].pb(id++);
        adj[v].pb(id++);
    }

    bool bfs()
    {
        while( ! q.empty() )
        {
            int curr = q.front();
            q.pop();
            for( auto e : adj[curr] )
            {
                if( edges[e].cap - edges[e].flow < 1 )
                    continue;
                if( level[ edges[e].v ] != -1 )
                    continue;
                level[ edges[e].v ] = level[ edges[e].u ] + 1;
                q.push( edges[e].v );
            }
        }
        return level[t] != -1;
    }

    ll dfs( int u, ll flow )
    {
        if( flow == 0 )
            return 0;
        if( u == t )
            return flow;
        for( int& cid = next[u]; cid < sz(adj[u]); cid++ )
        {
            int e = adj[u][cid];
            int v = edges[e].v;

            if( level[edges[e].u] + 1 != level[v] || edges[e].cap - edges[e].flow < 1 )
                continue;
            ll f = dfs( v, min(flow, edges[e].cap - edges[e].flow ) );
            if( f == 0 )
                continue;
            edges[e].flow += f;
            edges[ e ^ 1 ].flow -= f;
            return f;
        }
        return 0;
    }

    ll maxFlow()
    {
        ll flow = 0;
        while( bfs() )
        {
            fill(all(next),0);
            for( ll f = dfs(s,INF); f != 0ll; f = dfs(s,INF) )
                flow += f;
            fill(all(level),-1);
            level[s] = 0;
            q.push(s);
        }
        return flow;
    }

    vii minCut()
    {
        vii ans;
        fill(all(level),-1);
        level[s] = 0;
        q.push(s);
        while( ! q.empty() )
        {
            int curr = q.front();
            q.pop();
            for( int id = 0; id < sz(adj[curr]); id++ )
            {
                int e = adj[curr][id];
                if( level[edges[e].v] == -1 && edges[e].cap - edges[e].flow > 0 )
                {
                    q.push(edges[e].v);
                    level[edges[e].v] = level[edges[e].u] + 1;
                }
            }
        }
        for( int i = 0; i < sz(level); i++ )
        {
            if( level[i] != -1 )
            {
                for( int id = 0; id < sz(adj[i]); id++ )
                {
                    int e = adj[i][id];
                    if( level[edges[e].v] == -1 && edges[e].cap - edges[e].flow == 0 )
                        ans.emplace_back(edges[e].u,edges[e].v);
                }
            }
        }
        return ans;
    }

    vii maximumMatching()
    {
        vii ans;
        fill(all(level),-1);
        level[s] = 0;
        q.push(s);
        while( ! q.empty() )
        {
            int curr = q.front();
            q.pop();
            for( int id = 0; id < sz(adj[curr]); id++ )
            {
                int e = adj[curr][id];
                if( level[edges[e].v] == -1 && edges[e].cap - edges[e].flow == 0 && edges[e].flow != 0ll )
                {
                    q.push(edges[e].v);
                    level[edges[e].v] = level[edges[e].u] + 1;
                }
            }
        }
        for( int i = 0; i < sz(level); i++ )
        {
            if( level[i] != -1 )
            {
                for( int id = 0; id < sz(adj[i]); id++ )
                {
                    int e = adj[i][id];
                    if( edges[e].u != s && edges[e].v != t && edges[e].cap - edges[e].flow == 0 && edges[e].flow != 0ll )
                        ans.emplace_back(edges[e].u,edges[e].v);
                }
            }
        }
        return ans;
    }
};

int main()
{
    fastIO();

    int n, m, k, a, b;
    ll maxPairs;
    vii pairs;

    cin >> n >> m >> k;

    Dinic flow(n+m+2,0,n+m+1);

    fori(boy,0,n+1)
        flow.addEdge(0,boy,1);

    fori(girl,n+1,n+m+1)
        flow.addEdge(girl,n+m+1,1);

    fori(i,0,k)
    {
        cin >> a >> b;
        flow.addEdge(a,n+b,1);
    }

    maxPairs = flow.maxFlow();
    pairs = flow.maximumMatching();

    cout << maxPairs << endl;
    fori(i,0,sz(pairs))
        cout << pairs[i].fi << " " << (pairs[i].se - n) << endl;;

    return 0;
}