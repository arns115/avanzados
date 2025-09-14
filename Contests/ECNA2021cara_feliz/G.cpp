#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string a, b, c, op, e; cin >> a >> op >> b >> e >> c;
  int n = (int)a.size(), m = (int)b.size(), sz = (int)c.size();
  for(int i = 1; i < n; i++){
    for(int j = 1; j < m; j++){
      string A = b.substr(0, j) + a.substr(i, n - i + 1);
      string B = a.substr(0, i) + b.substr(j, m - j + 1);
      string C = c;
      ll num1 = stoll(A), num2 = stoll(B), num3 = stoll(C);
      if(op == "*"){
        if(num1 * num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
      else{
        if(num1 + num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
    }
  }
  for(int i = 1; i < n; i++){
    for(int j = 1; j < sz; j++){
      string A = c.substr(0, j) + a.substr(i, n - i + 1);
      string B = b;
      string C = a.substr(0, i) + c.substr(j, sz - j + 1);
      ll num1 = stoll(A), num2 = stoll(B), num3 = stoll(C);
      if(op == "*"){
        if(num1 * num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
      else{
        if(num1 + num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
    }
  }
  for(int i = 1; i < sz; i++){
    for(int j = 1; j < m; j++){
      string A = a;
      string B = c.substr(0, i) + b.substr(j, m - j + 1);
      string C = b.substr(0, j) + c.substr(i, sz - i + 1);
      ll num1 = stoll(A), num2 = stoll(B), num3 = stoll(C);
      if(op == "*"){
        if(num1 * num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
      else{
        if(num1 + num2 == num3){
          cout << A << " " << op << " " << B << " " << e << " " << C << endl;
          return 0;
        }
      }
    }
  }
}