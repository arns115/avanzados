#include <bits/stdc++.h>
#include <cmath>
#define ll long long
 
using namespace std;
 
 
const ll MOD = 1e9+7;
 
// MAX should be a power of 2 and >= 2*10^5
// FFT works with sizes that are powers of 2
// 2^18 = 262144 > 200000
const int MAX = pow(2,18); 
 
typedef complex<double> cd;
double PI = acos(-1);
 
// My favorite black box <3
vector<cd> fft(vector<cd> a, int d = 1) {
    int n = a.size();
    vector<cd> r(n);
 
    for (int k = 0; k < n; k++) {
        int b = 0;
        for (int z = 1; z < n; z *= 2) {
            b *= 2;
            if (k & z)
                b++;
        }
        r[b] = a[k];
    }
 
    for (int m = 2; m <= n; m *= 2) {
        cd wm = exp(cd{0, d * 2 * PI / m});
 
        for (int k = 0; k < n; k += m) {
            cd w = 1;
            for (int j = 0; j < m / 2; j++) {
                cd u = r[k + j];
                cd t = w * r[k + j + m / 2];
                r[k + j] = u + t;
                r[k + j + m / 2] = u - t;
                w = w * wm;
            }
        }
    }
 
    if (d == -1) {
        for (int i = 0; i < n; i++)
            r[i] /= n;
    }
 
    return r;
}
 
void solve() {
    int n, m;
    cin>>n>>m;
 
    vector<int> s(n), msk(m);

    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    for(int i = 0; i < m; i++){
        cin >> msk[i];
    }

    // The problem shifts the mask from left to right
    // and we notice that if we reverse the mask and
    // calculate the convolution of the signal and the
    // reversed mask we will get all products between terms
    // as if we shift the original signal from left to right
    reverse(msk.begin(), msk.end());

    // Build the complex double vectors
    vector<cd> a(2*MAX,cd(0,0)), b(2*MAX,cd(0,0));
    
    for(int i=0; i<n; i++){
        a[i]+=cd(s[i],0);
    }
    
    
    for(int i=0; i<m; i++){
        b[i]+=cd(msk[i],0);
    }
    
    // Calculate FFT for both arrays
    auto A = fft(a);
    auto B = fft(b);
    vector<cd> C(2*MAX);

    // Calculate convolution in frequency domain
    for(int i = 0; i < 2*MAX; i++){
        C[i] = A[i] * B[i];
    }

    // Inverse FFT to get back to time domain
    auto conv = fft(C, -1);
    
    for(int i = 0; i < n+m-1; i++){
        cout << (ll)round(conv[i].real()) << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}