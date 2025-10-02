struct Node{
	int v;
	int cnt = 0;
	Node* nxt[2];
	Node(int __v){
		v = __v;
		cnt = 0;
		nxt[0] = nxt[1] = NULL;
	}
};

struct Trie{
	typedef Node* pnode;
	pnode root;
	const int B = 30;

	void insert(int val){
		pnode cur = root;
		for(int i=B;i>=0;i--){
			bool b = val>>i&1;
			if(cur->nxt[b]==NULL)cur->nxt[b] = new Node(b);
			cur = cur->nxt[b];
			cur->cnt++;
		}
	}

	pnode erase(pnode cur, int val, int i) {
		if (cur == NULL)return NULL;
		cur->cnt--;
		if (i < 0) {
			if (cur->cnt == 0) {
				delete cur;
				return NULL;
			}
			return cur;
		}

		bool b = (val >> i) & 1;
		cur->nxt[b] = erase(cur->nxt[b], val, i - 1);

		if (cur->cnt == 0) {
			delete cur;
			return NULL;
		}

		return cur;
	}

	int query(int val){
		pnode cur = root;
		int ans = 0;
		for(int i = B;i>=0;i--){
			bool b = val>>i&1;
			if(cur->nxt[!b])cur = cur->nxt[!b],ans<<=1,ans++;
			else cur = cur->nxt[b],ans<<=1;
		}
		return ans;
	}
};

