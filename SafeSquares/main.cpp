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

#define LARGE 3005
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int R, C, K;
int M[LARGE];
int mark[LARGE][LARGE];
int TS[LARGE][LARGE];

bool test(int x, int y, int r) {
  return TS[x][y] + TS[x - r][y - r] - TS[x - r][y] - TS[x][y - r];
}

ll solve() {
  memset(M, 0, sizeof M);
  memset(TS, 0, sizeof TS);

  ll res = 0;
  inc (i, 1, R + 1) {
    inc (j, 1, C + 1) {
      M[j] += (mark[i][j]) ? 1 : 0;
      TS[i][j] = TS[i][j - 1] + M[j];
      int d = 0, u = min(i, j);
      while (d < u) {
        int r = (d + u) >> 1;
        if (test(i, j, r + 1)) u = r;
        else d = r + 1;
      }
      res += d;
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
    scanf("%d %d %d", &R, &C, &K);
    memset(mark, 0, sizeof mark);
    int x, y;
    inc (i, 1, K + 1) {
      scanf("%d %d", &x, &y);
      mark[x + 1][y + 1] = 1;
    }
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

