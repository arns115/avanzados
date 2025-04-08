class SAT{
private:
	int n;
	vector<vi> adj;
	vector<vi> adj_t;
	vector<vi> adj_cond;
	vi order;
	vector<bool> vis;
	vi who;
	vector<bool> ans;
	int comp;
public:

	SAT(int m=0){
		n = (m<<1);
		adj.resize(n);
		adj_t.resize(n);
		vis.assign(n,0);
		who.assign(n,-1);
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
	
	// (a v b)
	void addOR(int a, bool af, int b, bool bf) {
		a += a + (af ^ 1);
		b += b + (bf ^ 1);
		adj[a ^ 1].push_back(b);
		adj[b ^ 1].push_back(a);
		adj_t[b].push_back(a ^ 1);
		adj_t[a].push_back(b ^ 1);
	}

	//( a XOR b)
	void addXOR(int a, bool af, int b, bool bf) {
		addOR(a, af, b, bf);
		addOR(a, !af, b, !bf);
	}
	//(a -> b)
	void _add(int a,bool af,int b,bool bf) {
		a += a + (af ^ 1);
		b += b + (bf ^ 1);
		adj[a].push_back(b);
		adj_t[b].push_back(a);
	}

	//(a->b)^(b->a)
	void add(int a,bool af,int b,bool bf) {
		_add(a, af, b, bf);
		_add(b, !bf, a, !af);
	}

	bool solve_SAT(){
		for(int i=0;i<n;i++)
			if(!vis[i])dfs1(i);

		comp = -1;
		vis.assign(n,0);
		for(int i=sz(order)-1;i>=0;i--)
			if(!vis[order[i]]){
				comp++;
				dfs2(order[i]);
			}
		ans.assign(n/2,0);
		for(int i=0;i<n;i+=2){
			if(who[i] == who[i+1])return 0;
			ans[i/2] = (who[i] > who[i+1]);
		}
		return 1;
	}

	bool operator[](int i){
		return ans[i];
	}

};
