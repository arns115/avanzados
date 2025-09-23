struct Node{
  //Info del nodo del segment tree
};

struct Lazy{
  //Aqui metes los booleanos de si esta seteado y tus datos

};

Node operator+(Node a,Node b){
  //Aqui va como quieres mergear los nodos
}

struct Segment_Tree{
	
	int n;
	vector<Node> tree;
	vector<Lazy> lazy;
 
	Segment_Tree(int x = 1e5+10){
		n = x;
		tree.resize(4*n);
		lazy.resize(4*n);
	}
 
	void push_set(int v,int l,int r){
		if(!lazy[v].has_set)return;
		tree[v].val = lazy[v].val*(r-l+1);
		
		if(l!=r){
			lazy[v<<1] = lazy[v];
			lazy[(v<<1)|1] = lazy[v];
		}
		lazy[v].has_set = 0;
		lazy[v].val = 0;
	}
 
	void push_sum(int v,int l,int r){
		if(!lazy[v].has_sum)return;
		tree[v].val = tree[v].val+lazy[v].val*(r-l+1);
		if(l!=r){
			lazy[v<<1].val = lazy[v<<1].val + lazy[v].val;
			lazy[(v<<1)|1].val = lazy[(v<<1)|1].val + lazy[v].val;
			if(!lazy[v<<1].has_set)lazy[v<<1].has_sum=1;
			if(!lazy[(v<<1)|1].has_set)lazy[(v<<1)|1].has_sum=1;
		}
		lazy[v].has_sum = 0;
		lazy[v].val= 0;
	}
 
	void update(int pos,ll val,int v,int tl, int tr){
		if(tl == tr)tree[v] = {val};
		else{
			int tm = tl+(tr-tl)/2;
			if(pos <= tm)update(pos,val,v<<1,tl,tm);
			else update(pos,val,(v<<1)+1,tm+1,tr);
			tree[v] = tree[v<<1]+tree[(v<<1)+1];
		}
	}
 
	void update_set(int v,int tl,int tr,int l,int r,ll val){
		push_set(v,tl,tr);
		push_sum(v,tl,tr);
		if(l>tr||r<tl)return;
		if(tl>= l && tr <=r){
			lazy[v].has_set=1;
			lazy[v].has_sum=0;
			lazy[v].val=val;
			push_set(v,tl,tr);
			return;
		}
		int tm = tl+(tr-tl)/2;
		update_set(v<<1,tl,tm,l,r,val);
		update_set((v<<1)|1,tm+1,tr,l,r,val);
		tree[v] = tree[v<<1]+tree[(v<<1)|1];
	}
	
	void update_sum(int v,int tl,int tr,int l,int r,ll val){
		push_set(v,tl,tr);
		push_sum(v,tl,tr);
		if(l>tr||r<tl)return;
		if(tl>= l && tr <=r){
			lazy[v].has_sum=1;
			lazy[v].val += val;
			push_sum(v,tl,tr);
			return;
		}
		int tm = tl+(tr-tl)/2;
		update_sum(v<<1,tl,tm,l,r,val);
		update_sum((v<<1)|1,tm+1,tr,l,r,val);
		tree[v] = tree[v<<1]+tree[(v<<1)|1];
	}
 
	Node query(int v ,int tl ,int tr ,int l ,int r){
		push_set(v,tl,tr);
		push_sum(v,tl,tr);
		if(l>tr||r<tl)return {0};
		if(tl>= l && tr <= r )
			return tree[v];
		int tm = tl+(tr-tl)/2;
		return query(v<<1,tl,tm,l,r)+query((v<<1)|1,tm+1,tr,l,r);
	}
 
};
