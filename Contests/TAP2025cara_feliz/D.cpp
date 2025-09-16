#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int A, B; cin >> A >> B;
  int n = A + B;
  vector<int> a(n), b(n);
  vector<string> s(n), t(n);
  for(int i = 0; i < n; i++){
    cin >> a[i] >> s[i] >> b[i] >> t[i];
  }
  map<string, vector<array<int, 2>>> pos;
  vector<int> winner(n, 0);
  set<int> st, st1;
  st.insert(n);
  st1.insert(1);
  for(int i = 0; i < n; i++){
    if(s[i] == t[i]){
      st.insert(i);
      st1.insert(-i);
      if(a[i] > b[i]){
        winner[i] = 1;
      }
      else winner[i] = 2;
      pos[s[i]].push_back({i, 3});
    } 
    else{
      pos[s[i]].push_back({i, 1});
      pos[t[i]].push_back({i, 2});
    }
  }
  for(int i = 0; i < n; i++){
    if(winner[i] == 0){
      if(i) winner[i] = winner[i - 1];
      else winner[i] = 1;
    }
  }
  for(int i = 0; i < n; i++){
    if(winner[i] == 1) A--;
    else B--;
  }
  for(auto [ss, vec]: pos){
    int AA = A, BB = B;
    for(int i = 0; i < (int)vec.size(); i++){
      if(vec[i][1] == 3) continue;
      int curWinner = vec[i][1];
      int next = *st.lower_bound(vec[i][0]);
      if(i  + 1 < (int)vec.size()){
        next = min(next, vec[i + 1][0]);
      }
      int last = *st1.lower_bound(-vec[i][0]);
      last = -last;
      int lastWinner;
      if(i == 0 || last != vec[i - 1][0]){
        if(last == -1) last = 0;
        lastWinner = winner[last];
      }
      else{
        lastWinner = vec[i - 1][1];
        if(lastWinner == 3){
          if(a[vec[i - 1][0]] > b[vec[i - 1][0]]) lastWinner = 1;
          else lastWinner = 2;
        }
      }
      if(curWinner == lastWinner){
        continue;
      }
      if(curWinner == 1){
        BB += (next - vec[i][0]);
        AA -= (next - vec[i][0]);
      }
      else{
        AA += (next - vec[i][0]);
        BB -= (next - vec[i][0]);
      }
    }
    if(AA == 0 && BB == 0){
      cout << ss << endl;
      return 0;
    }
  }
  cout << "*" << endl;
}
