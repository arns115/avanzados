#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = 1e17;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	vector<vector<ll>> a(n, vector<ll>(n));
	vector<ll> S(1 << n, 0), dp(1 << n, -inf);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
				cin >> a[i][j];
		}
	}	
	for(int s = 0; s < (1 << n); s++){
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				if((s & (1 << i)) && (s & (1 << j))){
					S[s] += a[i][j];
				}
			}
		}
	}
	dp[0] = 0;
	for(int s = 1; s < (1 << n); s++){
		for(int mk = s; ; mk = (mk - 1) & s){
			dp[s] = max(dp[s], dp[mk] + S[s ^ mk]);
		  if(mk == 0){
				break;
			}	
		}
	}
	cout << dp[(1 << n) - 1] << endl;
}
