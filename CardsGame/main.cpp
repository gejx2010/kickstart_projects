#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <unordered_map>
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

#define LARGE 200
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, N = 0;
ll A[LARGE], B[LARGE];
ll sum[LARGE][LARGE];
set<int> sset[LARGE][LARGE];

ll check(set<int>& sv, set<tpl>& se, ll l) {
  if (!sv.count(l)) {
    for (auto v: sv) {
      se.erase(mt(sum[v][l], v, l));
    }
    sv.insert(l);
    for (int i = 1; i <= N; ++i) {
      if (!sv.count(i)) {
        se.insert(mt(sum[l][i], l, i));
      }
    }
  }
}

ll ssolve(set<int> sv, set<tpl> se) {
  if (se.empty()) return 0;
  //PRV(sv);
  //PR(sv.size());
  ll e, l, r;
  tie(e, l, r) = *(se.begin());
  //PR(e);
  //PR(l);
  //PR(r);
  check(sv, se, l);
  check(sv, se, r);
  return e + ssolve(sv, se);
}

ll solve() {
  // clean
  memset(sum, 0, sizeof sum);
  // compute sum
  ll e = LLONG_MAX, l = 0, r = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j) 
      if (i != j) {
        sum[i][j] = min(A[i] ^ B[j], A[j] ^ B[i]);
        if (sum[i][j] < e) {
          e = sum[i][j];
          l = i; r = j;
        }
      }
  set<int> sv;
  sv.insert(l);
  sv.insert(r);
  set<tpl> se;
  for (int i = 1; i <= N; ++i) {
    if (!sv.count(i)) {
      se.insert(mt(sum[l][i], l, i));
      se.insert(mt(sum[r][i], r, i));
    }
  }
  return e + ssolve(sv, se);
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
    for (int j = 1; j <= N; ++j)
      scanf("%lld", &A[j]);
    for (int j = 1; j <= N; ++j)
      scanf("%lld", &B[j]);
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

