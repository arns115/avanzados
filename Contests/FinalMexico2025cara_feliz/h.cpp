#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

int main(){
    int n; cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0, mx = -1;
    for(int i = 0; i < n; i++){
        if(a[i] > mx){
            ans++;
            mx = max(mx, a[i]);
        }
    }
    cout << ans << endl;
}