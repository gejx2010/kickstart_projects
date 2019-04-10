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

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 201
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int R, C;
int H[LARGE][LARGE];
int M[LARGE][LARGE];
int L[LARGE][LARGE];
int N[LARGE][LARGE];
bool changed;

void scanf_row(int n) {
  int bg = 1, ed = C, cl = 0;
  while (bg <= ed) {
    cl = H[n][bg];
    while (H[n][bg] < H[n][ed]) {
      if (H[n][bg] < cl) M[n][bg] = cl;
      else M[n][bg] = cl = H[n][bg];
      ++bg;
    }
    cl = H[n][ed];
    while (bg <= ed && H[n][ed] <= H[n][bg]) {
      if (H[n][ed] < cl) M[n][ed] = cl;
      else M[n][ed] = cl = H[n][ed];
      --ed;
    }
  }
}

void scanf_col(int n) {
  int bg = 1, ed = R, cl = 0;
  while (bg <= ed) {
    cl = H[bg][n];
    while (H[bg][n] < H[ed][n]) {
      if (H[bg][n] < cl) {
        L[bg][n] = cl;
      } else {
        L[bg][n] = cl = H[bg][n];
      }
      ++bg;
    }
    cl = H[ed][n];
    while (bg <= ed && H[ed][n] <= H[bg][n]) {
      if (H[ed][n] < cl) {
        L[ed][n] = cl;
      } else {
        L[ed][n] = cl = H[ed][n];
      }
      --ed;
    }
  }
}

int min_sur(int i, int j) {
  int res = INT_MAX;
  if (1 < i) res = min(res, N[i - 1][j]);
  if (1 < j) res = min(res, N[i][j - 1]);
  if (i < R) res = min(res, N[i + 1][j]);
  if (j < C) res = min(res, N[i][j + 1]);
  return res;
}

void scanf_whole() {
  changed = false;
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    int m = min_sur(i, j);
    if (m < H[i][j]) m = H[i][j];
    if (m < N[i][j]) {
      changed = true;
      N[i][j] = m;
    }
  }  
}

int cmp() {
  int res = 0;
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    debug("%d, %d, N: %d, H: %d\n", i, j, N[i][j], H[i][j]);
    res += N[i][j] - H[i][j];
  }
  return res;
}

int solve() {
  inc (i, 1, R + 1) scanf_row(i);
  inc (i, 1, C + 1) scanf_col(i);
  debug("before\n");
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    N[i][j] = min(L[i][j], M[i][j]);
    debug("%d, %d, N: %d, H: %d\n", i, j, N[i][j], H[i][j]);
  }
  debug("after\n");
  changed = true;
  while (changed) scanf_whole();
  return cmp();
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
    scanf("%d %d", &R, &C);
    inc (j, 1, R + 1) inc (k, 1, C + 1) scanf("%d", &H[j][k]);
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

