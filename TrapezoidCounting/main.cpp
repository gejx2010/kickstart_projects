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
#include <numeric>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef vector<pri> vpri;
typedef vector<pri> vtpi;

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 20000
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int N, NN;
ll L[LARGE];
ll M[LARGE];
ll C[LARGE];
ll Q[LARGE]; // for points query
ll S[LARGE]; // for sets query
ll NS[LARGE]; // for negetive sets query

int query(ll n) {
  //debug("query %lld\n", n);
  auto it = lower_bound(M + 1, M + NN + 1, n);
  int idx = it - M;
  //debug("retudn idx: %d\n", idx);
  if (idx <= 1) return 0;
  return Q[idx - 1];
}

ll solve() {
  sort(L + 1, L + N + 1);
  // build M & C
  int rk = 0;
  C[rk] = 0;
  for (int i = 1; i <= N; ++i) {
    if (L[i] == M[rk]) ++C[rk];
    else {
      ++rk;
      M[rk] = L[i];
      C[rk] = 1;
    }
  }
  NN = rk; 
  // build Q
  Q[0] = 0;
  for (int i = 1; i <= NN; ++i) Q[i] = Q[i - 1] + C[i];
  // build S
  S[0] = 0;
  for (int i = 1; i <= NN; ++i) S[i] = S[i - 1] + C[i] * Q[i - 1];
  // compute res
  ll res = 0;
  for (int i = 1; i <= NN; ++i) {
    if (2 <= C[i]) {
      ll c1 = C[i];
      ll c2 = (c1 * (c1 - 1)) >> 1;
      ll c3 = (C[i] < 3) ? 0 : c1 * (c1 - 1) * (c1 - 2) / 6;
      res += c2 * S[i - 1] + c3 * Q[i - 1];
      // query c1 < m < 3 * c1
      ll n = query(3 * M[i]);
      res += c3 * (n - Q[i]);
      // cnt v2 * v2
      for (int j = i + 1; j <= NN; ++j) {
        n = query(M[j] + (M[i] << 1));
        res += c2 * C[j] * (n - Q[j]);
      }
      // cnt v1 * v2
      for (int j = 1; j < i; ++j) {
        n = query(M[j] + (M[i] << 1));
        res += c2 * C[j] * (n - Q[i]);
      }
    }
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
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &L[i]);
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

