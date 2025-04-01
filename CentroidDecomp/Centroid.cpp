class Centroid{
private:
	vector<vi> tree;
	vi par;
	vi sub;
	vector<bool> check;
	int n;
public:	
	Centroid(vector<vi> &t):tree(t){
		n = tree.size();
		par.resize(n);
		sub.resize(n);
		check.resize(n);
		build();
	}

	void build(int u = 0, int p = -1){
		dfs(u, p);
		int c = get_centroid(u,p,sub[u]);
		check[c] = 1;
		par[c] = p+1;

		for (auto v : tree[c]){
			if(!check[v])
				build(v, c);
		}
	
	}

	int dfs(int u,int p){
		if(check[u])return 0;
		sub[u] = 1;
		for(int v:tree[u])
			if(v!=p)sub[u]+=dfs(v,u);

		return sub[u];
	}

	int get_centroid(int u,int p,int x){
		for(auto v:tree[u])
			if(v!=p && sub[v]*2>x && !check[v])return get_centroid(v,u,x);

		return u;
	}

	int operator[](int i){
		return par[i];
	}
};
