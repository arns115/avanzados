#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

int main(){
    string s; cin >> s;
    int n = sz(s);
    vector<string> a = {"ha", "boooo", "bravo"};
    int ans = 0;
    vector<int> z = {1, -1, 3};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++){
            int d = 1;
            for(int k = 0; k < (int)a[j].size(); k++){
                if(k + i >= n){
                    d = 0;
                    break;
                }
                if(a[j][k] != s[i + k]){
                    d = 0;
                    break;
                }
            }
            if(d) ans += z[j];
        }
    }
    cout << ans << endl;
}