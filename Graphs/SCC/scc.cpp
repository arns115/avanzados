class SCC{
private:
	int n;
	vector<vi> adj;
	vector<vi> adj_t;
	vector<vi> adj_cond;
	vi order;
	vector<bool> vis;
	vi who;
	int comp;
public:
	SCC(int n,vector<vi> &a,vector<vi>&b):n(n),adj(a),adj_t(b){
		comp = -1;
		who.resize(n);
		vis.resize(n);
		//Get time of entrance
		for(int i=0;i<n;i++)
			if(!vis[i])dfs1(i);
		
		vis.assign(n,0);
		//getting scc vi topo sort
		for(int i=n-1;i>=0;i--)
			if(!vis[order[i]]){
				comp++;
				dfs2(order[i]);
			}
		//get condense graph
		adj_cond.resize(comp+1);
		for(int u=0;u<n;u++)
			for(auto v:adj[u])
				if(who[v]!=who[u])
					adj_cond[who[u]].pb(who[v]);
				
	}

	void dfs1(int u) {
		vis[u] = true;
		for (int v:adj[u])
			if (!vis[v])dfs1(v);
		order.pb(u);
	}

	void dfs2(int u) {
		vis[u] = 1;
		for (int v : adj_t[u])
			if (!vis[v])dfs2(v);
		who[u] = comp;
	}
};
