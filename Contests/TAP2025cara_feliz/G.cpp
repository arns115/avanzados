#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(0);
  int a, b, c; cin >> a >> b >> c;
  cout << ((b - a) % c ? "N" : "S") << endl;
}