#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9+7;

vector<long long> KMP(vector<long long> s){
  long long n=(long long)s.size();
  vector<long long> pf(n, 0);
  for(long long i=1;i<n;i++){
    long long j=pf[i-1];
    while(j>0 && s[i]!=s[j]){
      j=pf[j-1];
    }
    if(s[i]==s[j]){
      pf[i]=j+1;
    }
  }
  return pf;
}

const long long kMaxV = 1e6;

long long sieve[kMaxV + 1];

//stores some prime (not necessarly the minimum one)
void primes()
{
  for (long long i = 4; i <= kMaxV; i += 2)
    sieve[i] = 2;
  for (long long i = 3; i <= kMaxV / i; i += 2)
  {
    if (sieve[i])
      continue;
    for (long long j = i * i; j <= kMaxV; j += i)
      sieve[j] = i;
    }
}

vector<long long> PrimeFactors(long long x)
{
  if (x == 1)
    return {};

  vector<long long> primes;
  while (sieve[x])
  {
    primes.push_back(sieve[x]);
    x /= sieve[x];
  }
  primes.push_back(x);
  sort(primes.begin(),primes.end());
  return primes;
}

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if((a - b) % g != 0)return -1; 
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

void get_ans(vector<pair<long long,long long>> v){
  vector<long long> a(1000006,-1);
  map<long long,long long> b;
  for(long long i =0;i<v.size();i++){
    vector<long long> aux = PrimeFactors(v[i].first);
    if(aux.size()==0)continue;
    long long act = aux[0];
    for(long long j = 1;j<aux.size();j++){
      if(a[act]!=-1 && a[act]!=v[i].second%act){
        cout<<"IMPOSSIVEL"<<endl;
        return;
      }
      a[act]=v[i].second%act;
      b[aux[j-1]] = max(b[aux[j-1]],act);
      if(aux[j] == aux[j-1]){
        act *= aux[j];
      }
      else{
        act = aux[j];
      }
    }
    if(a[act]!=-1 && a[act]!=v[i].second%act){
      cout<<"IMPOSSIVEL"<<endl;
      return;
    }
    a[act]=v[i].second%act;
    b[aux[aux.size()-1]] = max(b[aux[aux.size()-1]],act);
  }
  
  ll ans = -1;
  ll md =1;
  for(auto u:b){
    long long act = u.second;
    if(ans == -1){
      ans = a[act];
      md = act;
      continue;
    }
    if(ans>1e9){
      cout<<"DEMAIS"<<endl;
      return;
    }
    if(md>1e9){
      if(ans%act!=a[act]){
        cout<<"DEMAIS"<<endl;
        return;
      }
      else{
        continue;
      }
    }
    ans = crt(ans,md,a[act],act);
    md *= act;
  }
  if(ans == -1){
    cout<<0<<endl;
    return;
  }
  if(ans>1e9){
    cout<<"DEMAIS"<<endl;
    return;
  }
  cout<<ans<<endl;
}

int main(){
  ios_base::sync_with_stdio(false);  cin.tie(0);  cout.tie(0);
  primes();
  long long n;cin>>n;
  vector<long long> a(n),b(n),p(n);
  for(long long i = 0;i<n;i++)cin>>a[i];
  for(long long i = 0;i<n;i++)cin>>b[i];
  for(long long i = 0;i<n;i++){cin>>p[i];p[i]--;}
  
  vector<bool> vis(n,0);
  vector<pair<long long,long long>> cr;
  for(long long i = 0;i<n;i++){
    if(vis[i])continue;
    vector<long long> v;
    v.push_back(i);
    long long act = p[i];
    while(act!=i){
      v.push_back(act);
      vis[act] = 1;
      act = p[act];
    }
    vector<long long> r;
    for(long long i = 0;i<v.size();i++)r.push_back(b[v[i]]);
    r.push_back(-1);
    for(long long i = 0;i<v.size();i++)r.push_back(a[v[i]]);
    for(long long i = 0;i<v.size();i++)r.push_back(a[v[i]]);

    vector<long long> kmp = KMP(r);
    vector<long long> aux;
    for(long long i = 0;i<kmp.size();i++){
      if(kmp[i] == v.size()){
        aux.push_back(i-v.size()-v.size());
      }
    }
    if(aux.size()==0){
      cout<<"IMPOSSIVEL"<<endl;
      return 0;
    }
    long long auxx = aux.size()==1?v.size():aux[1]-aux[0];
    cr.push_back({auxx,(auxx-aux[0])%auxx});
  }
  get_ans(cr);
  
}
