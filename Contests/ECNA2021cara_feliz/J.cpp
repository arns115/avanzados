#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define pb push_back
#define ll long long
#define s second
#define f first
const int MOD = 1000000007;
#define INF 1e9
struct min_cartesian_tree
{
  vector<int> par;
  vector<vector<int>> sons;
  int root;
  void init(int n, vector<ll> &arr)
  {
    par.assign(n, -1);
    sons.assign(n, vector<int>(2, -1));
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
      int last = -1;
      while (!st.empty() && arr[st.top()] < arr[i])
      {
        last = st.top();
        st.pop();
      }
      if (!st.empty())
      {
        par[i] = st.top();
        sons[st.top()][1] = i;
      }
      if (last != -1)
      {
        par[last] = i;
        sons[i][0] = last;
      }
      st.push(i);
    }
    for (int i = 0; i < n; i++)
    {
      if (par[i] == -1)
      {
        root = i;
      }
    }
  }
};

min_cartesian_tree mct;
ll n;
ll ans=0;
ll al,ar;
void dfs(int a,ll l,ll r,vector<ll> &arr){
  if(a==-1)return;
  if(l>=n)return;
  if(r<0)return;
  // ans=min(ans,(r-l+1)*arr[a]);
  if(ans>(r-l+1)*arr[a]){
    ans=(r-l+1)*arr[a];
    al=l;
    ar=r;
  }
  // cout<<arr[a]<<" "<<l<<" "<<r<<endl;
  dfs(mct.sons[a][0],l,a-1,arr);
  dfs(mct.sons[a][1],a+1,r,arr);
}
void solve(){
  cin>>n;
  vector<ll> a(n);
  for(int i=0;i<n;i++){
    cin>>a[i];
    a[i]=-a[i];
  }
  
  mct.init(n,a);
  dfs(mct.root,0,n-1,a);
  cout<<al+1<<" "<<ar+1<<" "<<-ans<<endl;
  
}

int main() {
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  // int t;cin>>t;for(int T=0;T<t;T++)
  solve();
}