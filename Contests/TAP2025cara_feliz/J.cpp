#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<vector<int>> a(n), b(n);
  multiset<int> st, st1;
  for(int i = 0; i < n; i++){
    int k; cin >> k;
    for(int j = 0; j < k; j++){
      int u; cin >> u;
      a[i].push_back(u);
      st.insert(u);
    }
  }
  for(int i = 0; i < n; i++){
    int k; cin >> k;
    for(int j = 0; j < k; j++){
      int u; cin >> u;
      b[i].push_back(u);
      st1.insert(u);
    }
  }
  if(st != st1){
    cout << "N" << endl;
    return 0;
  }
  if(n >= 3){
    cout << "S" << endl;
    return 0;
  }
  if(n == 1){
    cout << (a == b ? "S" : "N") << endl;
    return 0;
  }
  if(a == b){
    cout << "S" << endl;
    return 0;
  }
  auto aa = a;
  while(aa[0].size() > b[0].size()){
    aa[1].push_back(aa[0].back());
    aa[0].pop_back();
  }
  if(aa == b){
    cout << "S" << endl;
    return 0;
  }
  auto aaa = a;
  while(aaa[1].size() > b[1].size()){
    aaa[0].push_back(aaa[1].back());
    aaa[1].pop_back();
  } 
  if(aaa == b){
    cout << "S" << endl;
    return 0;
  }
  cout << "N" << endl;
}