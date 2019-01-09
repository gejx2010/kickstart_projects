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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef tuple<int,int,int> tpi;
typedef vector<int> vi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << x << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 1000001
#define COMPILE false
#define TESTTIME true
#define MODULE_NUM 1000000007

// define initial parameters here
int T = 0;
ll N, K, x, y, C, D, E1, E2, F;
ll ini[LARGE], sum[LARGE], epo[LARGE];

ll pow_module(ll n, ll K) {
  if (n == 1) return 1;
  ll res = 1;
  while (K) {
    if (K & 1) res = (res * n) % MODULE_NUM;
    K >>= 1;
    n = (n * n) % MODULE_NUM;
  }
  return res;
}

ll compute_epo(int n) {
  ll left = (pow_module(n, K + 1) + MODULE_NUM - n) % MODULE_NUM;
  ll right = pow_module(n - 1, MODULE_NUM - 2);
  return (left * right) % MODULE_NUM;
}

int solve() {
  // compute a[n] * (N - n + 1), noted as sum[n]
  memset(sum, 0, sizeof sum);
  for (int i = 1; i <= N; ++i) {
    sum[i] = (ini[i] * (N - i + 1)) % MODULE_NUM;
  }
  // compute epo[n]
  ll s = K;
  epo[1] = K;
  for (int i = 2; i <= N; ++i) {
    s = (s + compute_epo(i)) % MODULE_NUM;
    epo[i] = s;
  }
  // multiply
  ll res = 0;
  for (int i = 1; i <= N; ++i) {
    res = (res + sum[i] * epo[i]) % MODULE_NUM;
  }
  return res;
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
    cin >> N >> K >> x >> y >> C >> D >> E1 >> E2 >> F;
    // compute x and y
    ll xx, yy;
    ini[1] = (x + y) % F;
    for (int i = 2; i <= N; ++i) {
      xx = (C * x + D * y + E1) % F;
      yy = (D * x + C * y + E2) % F;
      x = xx;
      y = yy;
      ini[i] = (x + y) % F;
    }
    // solve problem
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

