#include <bits/stdc++.h>
#include <vector>
#define fastIo() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
#define F first
#define S second
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

void solve() {
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].F;
        cin >> a[i].S;
    }

    vi distance(n-1);

    for(int i = 1; i < n; i++) {
        if(a[i].F == a[i-1].F) {
            distance[i-1] = abs(a[i].S - a[i-1].S);
        } else {
            distance[i-1] = abs(a[i].F - a[i-1].F);
        }
    }

    int max_l = 1, min_r=distance[0]-1;
    int total_distance = distance[0];

    for(int i = 1; i < n-1; i++) {

        int l = 0, r = 0;

        if((i+1) % 2 != 0) {
            l = 1 + total_distance;
            r = distance[i] - 1 + total_distance;
            total_distance += distance[i];
        }
        else {
            l = total_distance - (distance[i] - 1);
            r = total_distance - 1;
            total_distance -= distance[i];
        }

        max_l = max(max_l, l);
        min_r = min(min_r, r);
    }

    if(min_r < max_l) min_r = -1;
    cout << min_r << "\n";

}

int main() {
    fastIo();
    int t = 1;
    for(int i = 0; i < t; i++) solve();
}
