#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <stack>
#include <queue>
#include <cassert>
#include <tuple>
#include <set>
#include <bitset>
#include <climits>
#include <cfloat>
#include <numeric>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<pri> vpri;
typedef vector<pri> vtpi;

using prd = pair<double,double>;

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 1000000007
#define COMPILE false
#define TESTTIME true
#define COM 100005

// define initial parameters here
int T = 0;
ll A, B, N, K;
ll AK[COM];
ll BK[COM];

ll cmp_step(ll a, ll k, ll m) {
  ll r = 1;
  while (k) {
    if (k & 1) r = (r * a) % m;
    a = (a * a) % m;
    k >>= 1;
  }
  return r % m;
}

void cmp_less(ll a, ll k, ll n, ll* aa) {
  inc (i, 1, n + 1) 
    ++aa[cmp_step(i, a, k)];
}

ll cmp_same(ll n) {
  ll cnt = 0;
  inc (i, 1, n + 1) {
    ll f = cmp_step(i, A, K);
    ll s = cmp_step(i, B, K);
    if ((f + s) % K == 0) ++cnt;
  }
  return cnt;
}

ll solve() {
  memset(AK, 0, sizeof AK);
  memset(BK, 0, sizeof BK);
  cmp_less(A, K, K, AK);
  cmp_less(B, K, K, BK);
  ll t = (N / K) % LARGE;
  //PR(t);
  //PR(AK[0]);
  //PR(BK[0]);
  inc (i, 0, K) AK[i] = (AK[i] * t) % LARGE;
  inc (i, 0, K) BK[i] = (BK[i] * t) % LARGE;
  cmp_less(A, K, N % K, AK);
  cmp_less(B, K, N % K, BK);
  ll r = 0;
  inc (i, 0, K) {
    r += (i == 0) ? (AK[i] * BK[i]) % LARGE : (AK[i] * BK[K - i]) % LARGE;
    r %= LARGE;
  }
  //PR(r);
  ll s = cmp_same(K);
  s = (s * t) % LARGE;
  s += cmp_same(N % K);
  //PR(s);
  return (r + LARGE - s) % LARGE;
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    cin >> A >> B >> N >> K;
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

