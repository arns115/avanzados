#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define pb push_back
#define fi first
#define se second
#define sz(a) int(a.size())
#define endl "\n"
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int tc;

#define error(args...)                            \
  {                                               \
    cerr << "--- Debug tc=" << tc << " ---" endl; \
    string _s = #args;                            \
    replace(_s.begin(), _s.end(), ',', ' ');      \
    stringstream _ss(_s);                         \
    istream_iterator<string> _it(_ss);            \
    err(_it, args);                               \
    cerr << endl;                                 \
  }

void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
  cerr << *it << " = " << a << endl;
  err(++it, args...);
}

template <typename T>
void read_v(vector<T> &a)
{
  for (int i = 0; i < a.size(); i++)
    cin >> a[i];
}

constexpr ll INF_LL = LONG_LONG_MAX;
constexpr int INF_INT = INT_MAX;
constexpr int MOD = 1e9 + 7;

const int MAX_N = 1e6 + 1;
vi number_divisors(MAX_N);
vi mob_inv(MAX_N, 0);
vi alergies(MAX_N);

void calc_divisors(vi &nums)
{
  for (int i = 2; i < MAX_N; i++)
  {
    for (int j = i; j < MAX_N; j += i)
    {
      number_divisors[i] += nums[j];
    }
  }
}

void calc_mob()
{

  mob_inv[1] = 1;

  for (int i = 1; i < MAX_N; i++)
  {
    if (mob_inv[i])
    {
      mob_inv[i] = -mob_inv[i];
      for (int j = 2 * i; j < MAX_N; j += i)
      {
        mob_inv[j] += mob_inv[i];
      }
    }
  }
}

void calc_alergies()
{
  for (int i = 2; i < MAX_N; i++)
  {
    for (int j = i; j < MAX_N; j += i)
    {
      if (mob_inv[i] == 1)
      {
        alergies[j] += number_divisors[i];
      }
      else if (mob_inv[i] == -1)
      {
        alergies[j] -= number_divisors[i];
      }
    }
  }
}

long long binpow(long long a, long long b, long long m = MOD)
{
  a %= m;
  long long res = 1;
  while (b > 0)
  {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

void solve()
{
  int n;
  cin >> n;

  vi nums(MAX_N);

  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    nums[x]++;
  }

  calc_divisors(nums);
  calc_mob();
  calc_alergies();

  int q;
  cin >> q;

  while (q--)
  {
    int x;
    cin >> x;
    cout << binpow(2, n - alergies[x]) << endl;
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t = 1;

  for (tc = 1; tc <= t; tc++)
    solve();

  return 0;
}