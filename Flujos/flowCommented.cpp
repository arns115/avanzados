// Racso programmed here
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
#define all(v) v.begin(),v.end()
#define pb(x) push_back(x)
#define sz(x) (int)(x.size())
const ll INF = 1e17;

/**
 * @brief Represents a directed edge in a flow network.
 * @details Stores the edge's source, destination, capacity, and current flow.
 *          Used in max-flow algorithms like Dinic or Ford-Fulkerson.
 */
struct flowEdge
{
    int u;      ///< Source node of the edge (from).
    int v;      ///< Destination node of the edge (to).
    ll cap;     ///< Maximum flow capacity of the edge.
    ll flow = 0;///< Current flow through the edge (initially 0).
    flowEdge( int u, int v, ll cap ) : u(u), v(v), cap(cap) {}; // Contructor method.
};

/**
 * @brief Implementation of Dinic's max-flow algorithm.
 * @details Manages a flow network with BFS (Level Graph) and DFS (Blocking Flow) optimizations.
 */
struct Dinic
{
    vector<flowEdge> edges;///< All edges in the flow network (including reverse edges).
    vector<vi> adj;        ///< Adjacency list where 'adj[u]' stores indices of edges from node 'u'.
    int n;                 ///< Total number of nodes in the graph.
    int s;                 ///< Source node ("fuente", start of flow).
    int t;                 ///< Sink node ("sumidero", destination of flow).
    int id = 0;            ///< Counter for edge indexing.
    vi level;              ///< Stores the level (distance from 's') of each node during BFS.
    vi next;               ///< Optimization for DFS: tracks the next edge to explore for each node.
    queue<int> q;          ///< Queue for BFS traversal.

    /**
     * @brief Constructs a Dinic solver for a flow network.
     * @param n Number of nodes.
     * @param s Source node. 
     * @param t Sink node.
     */
    Dinic( int n, int s, int t ) : n(n), s(s), t(t)
    {
        adj.resize(n);       // Initialize adjacency list for `n` nodes.
        level.resize(n);     // Prepare level array for BFS.
        next.resize(n);      // Prepare next-edge array for DFS.
        fill(all(level),-1); // Mark all levels as unvisited (-1).
        level[s] = 0;        // The source has level 0.
        q.push(s);           // Start BFS from the source.
    }

    /**
     * @brief Adds a directed edge and its residual reverse edge to the flow network.
     */
    void addEdge( int u, int v, ll cap )
    {
        edges.emplace_back(u,v,cap);  // Original edge: u -> v.
        edges.emplace_back(v,u,0);    // Residual edge: v -> u.
        adj[u].pb(id++);
        adj[v].pb(id++);
    }

    /**
    * @brief Performs BFS to construct the level graph (Layered Network) from source 's' to sink 't'.
    * @details Assigns levels (minimum distances from 's') to all nodes and checks if 't' is reachable.
    *          Levels are used to guide the DFS phase in Dinic's algorithm.
    * @return bool True if the sink 't' is reachable (i.e., there exists an augmenting path), false otherwise.
    */
    bool bfs()
    {
        while( ! q.empty() )
        {
            int curr = q.front();
            q.pop();
            for( auto e : adj[curr] )
            {
                if( edges[e].cap - edges[e].flow < 1 ) // Skip saturated edges (no residual capacity).
                    continue;
                if( level[ edges[e].v ] != -1 ) // Skip already visited nodes (level assigned).
                    continue;
                // Assign level to the neighbor node.
                level[ edges[e].v ] = level[ edges[e].u ] + 1; // Next level = current + 1.
                q.push( edges[e].v ); // Add neighbor to the queue for further BFS.
            }
        }
        return level[t] != -1; // Return whether the sink 't' was reached (level[t] != -1).
    }

    /**
    * @brief Finds a blocking flow using DFS in the level graph constructed by BFS.
    * @param u Current node being processed.
    * @param flow Maximum flow that can be sent from 'u' to the sink 't'.
    * @return ll The amount of flow successfully sent to 't'.
    */
    ll dfs( int u, ll flow )
    {
        if( flow == 0 ) // No remaining flow to send.
            return 0;
        if( u == t )    // Reached the sink; return accumulated flow.
            return flow;
        // Explore edges from 'u' using 'next[u]' to avoid revisiting processed edges.
        for( int& cid = next[u]; cid < sz(adj[u]); cid++ )
        {
            int e = adj[u][cid]; // Index of the edge in 'edges'.
            int v = edges[e].v;  // Destination node of the edge.

            // Skip invalid edges:
            // 1. Not in the level graph (level[u] + 1 != level[v]). Just edges in exactly one leve ahead (ensures shortest paths).
            // 2. No residual capacity (cap - flow < 1).
            if( level[edges[e].u] + 1 != level[v] || edges[e].cap - edges[e].flow < 1 )
                continue;
            ll f = dfs( v, min(flow, edges[e].cap - edges[e].flow ) ); // Recursively send flow to 'v'.
            if( f == 0 ) // No flow could be sent via this edge.
                continue;
            // Update residual capacities:
            edges[e].flow += f;       // Increase flow in the original edge.
            edges[ e ^ 1 ].flow -= f; // Decrease flow in the reverse edge. (All reverse edges have distinct parity)
            return f;                 // Return the flow sent.
        }
        return 0; // No augmenting path found from 'u'.
    }

    /**
     * @brief Computes the maximum flow from source 's' to sink 't' using Dinic's algorithm.
     * @details Iterates through BFS and DFS phases to find the maximum flow.
                Accumulates flow while there exists augmention paths in the residual graph.
                Restart auxiliary structures for every new phase.
     * @return ll The maximum flow value.
     */
    ll maxFlow()
    {
        ll flow = 0; // Tracks the total flow sent.
        while( bfs() ) // While there are augmenting paths:
        {
            fill(all(next),0); // Reset 'next' for DFS.
            for( ll f = dfs(s,INF); f != 0ll; f = dfs(s,INF) ) // Send blocking flow in the level graph:
                flow += f;
            // Reset for next BFS phase:
            fill(all(level),-1);
            level[s] = 0;
            q.push(s);
        }
        return flow;
    }
    /**
     * @brief Finds edges belonging to the minimum cut after maxFlow().
     * @details First, it marks all the reachable nodes from 's' with an augmention path after obtained the max flow
                and all the saturated edges coming out from any of the nodes who belong to the min-cut.
                For 'minCut()' to work, 'maxFlow()' must be first executed to get the min-cut.
                If only is needed the value, is enough returning the value of 'maxFlow()'.
     * @return vii List of edges (u, v) in the min-cut. Its size is the minimum number of 'roads' to close.
     */
    vii minCut()
    {
        vii ans;
        fill(all(level),-1); // Reset levels.
        level[s] = 0;        // Mark source as reachable.
        q.push(s);
        while( ! q.empty() ) // BFS to mark nodes reachable from 's' in the residual graph.
        {
            int curr = q.front();
            q.pop();
            for( int id = 0; id < sz(adj[curr]); id++ ) // For every edge going out from 'curr'.
            {
                int e = adj[curr][id];
                // If 'v' is has not been visited yet, and the edge have residual capacity.
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
    
    /**
     * @brief Reconstructs the maximum bipartite matching after running 'maxFlow()'.
     * @details Every edge that belong to the original graph and have flow greater than zero, belongs to the matching.
                For 'maximumMatching()' to work, 'maxFlow()'.
     * @return vii List of matched pairs (boy, girl).
     */
    vii maximumMatching()
    {
        vii ans;
        fill(all(level),-1); // Reset levels.
        level[s] = 0;        // Mark source as reachable.
        q.push(s);
        while( ! q.empty() ) // BFS to mark nodes reachable via saturated edges with flow greater than zero.
        {
            int curr = q.front();
            q.pop();
            for( int id = 0; id < sz(adj[curr]); id++ )
            {
                int e = adj[curr][id];
                // If 'v' has not been visited yet, the edge is saturated and have flow greater than zero.
                if( level[edges[e].v] == -1 && edges[e].cap - edges[e].flow == 0 && edges[e].flow != 0ll )
                {
                    q.push(edges[e].v);
                    level[edges[e].v] = level[edges[e].u] + 1;
                }
            }
        }
        for( int i = 0; i < sz(level); i++ ) // Collect original edges (boy -> girl) that are saturated and have flow > 0.
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