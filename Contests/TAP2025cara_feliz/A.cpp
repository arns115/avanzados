#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s; cin >> s;
  string t= "TAP";
  int j = 0;
  for(char c: s){
    if(j < 3 && t[j] == c) j++; 
  }
  cout << (j == 3 ? "S" : "N") << endl;
}