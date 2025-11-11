#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

const int maxn = 300010;

struct min_t{
    ll val;
    static const ll null_v = 1LL << 61;
    min_t(): val(null_v){}
    min_t(ll v): val(v){}
    min_t op(min_t &other){
        return min_t(min(val, other.val));
    }
    min_t lazy_op(min_t &v, int size){
        return min_t(val + v.val);
    }
};

template<typename num_t>
struct segtree{
    int n; 
    vector<num_t> tree, lazy;

    void init(int s){
        n = s;
        tree.assign(4 * n, num_t());
        lazy.assign(4 * n, num_t(0));
        init(0, 0, n - 1);
    }

    num_t init(int i, int l, int r){
        if(l == r) return tree[i] = num_t(l);

        int mid = (l + r) / 2;
        num_t left = init(2 * i + 1, l, mid);
        num_t right = init(2 * i + 2, mid + 1, r);
        return tree[i] = left.op(right);
    }

    void update(int l, int r, num_t v){
        if(l > r) return;
        update(0, 0, n - 1, l, r, v);
    }

    num_t update(int i, int tl, int tr, int ql, int qr, num_t v){
        eval_lazy(i, tl, tr);

        if(tr < ql || qr < tl) return tree[i];
        if(ql <= tl && tr <= qr){
            lazy[i].val += v.val;
            eval_lazy(i, tl, tr);
            return tree[i];
        }

        int mid = (tl + tr) / 2;
        num_t a = update(2 * i + 1, tl, mid, ql, qr, v);
        num_t b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
        return tree[i] = a.op(b);
    }

    pair<ll, int> query(int i, int tl, int tr){
        eval_lazy(i, tl, tr);
        if(tl == tr){
            return {tree[i].val, tl};
        }
        int mid = (tl + tr) / 2;
        eval_lazy(2 * i + 1, tl, mid);
        eval_lazy(2 * i + 2, mid + 1, tr);
        if(tree[2 * i + 1].val == tree[0].val){
            return query(2 * i + 1, tl, mid);
        }
        else{
            return query(2 * i + 2, mid + 1, tr);
        }
    }

    void eval_lazy(int i, int l, int r){
        tree[i] = tree[i].lazy_op(lazy[i], r - l + 1);
        if(l != r){
            lazy[2 * i + 1].val += lazy[i].val;
            lazy[2 * i + 2].val += lazy[i].val;
        }
        lazy[i] = num_t(0);
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    vector<char> c(n);
    for(int i = 0; i < n ;i++){
        cin >> c[i];
        cin >> a[i];
    }
    segtree<min_t> st;
    st.init(maxn);
    int ans = 0, cnt = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < maxn){
            if(c[i] == '-'){
                st.update(a[i], maxn - 1, 1);
                cnt--;
            }
            else{
                cnt++;
                st.update(a[i], maxn - 1, -1);
            }
        }
        else if(c[i] == '-') ans--;
        else if(c[i] == '+') ans++;
        auto [u, v] = st.query(0, 0, maxn - 1);
        ll val = v - u;
        cout << ans + v + (cnt - val) << " ";
    }
    cout << endl;
}