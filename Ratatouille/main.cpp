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

#define LARGE 51
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N, P;
int R[LARGE];
int Q[LARGE][LARGE];
pri L[LARGE][LARGE];
bool hs[LARGE][LARGE];
int lb, rb;

int select(int ln) {
  PR(lb);
  PR(rb);
  if (rb < lb) return 0;
  if (N <= ln) return 1;
  for (int i = 0; i < P; ++i) {
    if (hs[ln][i]) continue;
    if (L[ln][i].second < L[ln][i].first) continue;
    if (L[ln][i].second < lb) continue;
    if (rb < L[ln][i].first) break;
    int flb = lb, frb = rb;
    lb = max(lb, L[ln][i].first);
    rb = min(rb, L[ln][i].second);
    hs[ln][i] = true;
    PR("select");
    PR(ln);
    PR(i);
    if (select(ln + 1)) return 1;
    // backtrace
    lb = flb, rb = frb;
    hs[ln][i] = false;
  }
  return 0;
}

int solve() {
  // sort
  for (int i = 0; i < N; ++i) sort(Q[i], Q[i] + P);
  // build L
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < P; ++j) {
      double ld = (double)Q[i][j] / (1.1 * R[i]);
      double rd = (double)Q[i][j] / (0.9 * R[i]);
      debug("%.20f\n", ld);
      debug("%.20f\n", rd);
      int n = ceil(ld);
      int m = floor(rd);
      if (Q[i][j] <= 1.1 * (n - 1) * R[i]) n -= 1;
      if (0.9 * (m + 1) * R[i] <= Q[i][j]) m += 1;
      PR(Q[i][j]);
      PR(R[i]);
      PR(n);
      PR(m);
      L[i][j] = mp(n, m);
    }
  }
  // compute
  int cnt = 0;
  memset(hs, 0, sizeof hs);
  for (int i = 0; i < P; ++i) {
    PR(0);
    PR(i);
    lb = L[0][i].first, rb = L[0][i].second;
    if (lb <= rb) cnt += select(1);
  }
  return cnt;
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
    scanf("%d %d", &N, &P);
    for (int j = 0; j < N; ++j) scanf("%d", &R[j]);
    for (int j = 0; j < N; ++j)
      for (int k = 0; k < P; ++k)
        scanf("%d", &Q[j][k]);
    int ans = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, ans);
  }
  return 0;
}

