/***************************************
Author: spgoal
Date: Mon, Apr/29/2019, 00:31:16
Lang: C++
***************************************/

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
#define PRA(x,sz) cerr << #x << ": " << endl; for (int xit = 0; xit < (sz); ++(xit)) cerr << (x)[xit] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& xit: x) cerr << xit << ' '; cerr << endl;
#define PRM(x) cout << #x << ": " << endl; for (auto& xit: x) cout << (xit).first << ": " << (xit).second << endl; cout << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype((a) + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)
#define lch(x) ((x) << 1)
#define rch(x) (((x) << 1) + 1)

#define SMALL 2001
#define LARGE 200001
#define COMPILE false
#define TESTTIME true
#define MOD 1000000007

// define initial parameters here
int T = 0;
int P, Q;
int X[SMALL], Y[SMALL];
char D[SMALL];
int xres, yres, dsum, fsum;
vpri xm[LARGE], ym[LARGE];
si xs, ys;
int dp;

int init_sum() {
  inc (i, 1, P + 1) xm[i].clear(), ym[i].clear();
  xs.clear(), ys.clear();
  fsum = 0;
  xs.insert(0), ys.insert(0);
  xs.insert(Q), ys.insert(Q);
  inc (i, 1, P + 1) {
    xm[X[i]].pb({Y[i], D[i]});
    ym[Y[i]].pb({X[i], D[i]});
    xs.insert(X[i]);
    if (X[i] < Q) xs.insert(X[i] + 1);
    ys.insert(Y[i]);
    if (Y[i] < Q) ys.insert(Y[i] + 1);
    if (0 < X[i] && D[i] == 'W') ++fsum;
    if (0 < Y[i] && D[i] == 'S') ++fsum;
  }
}

void solve2() {
  // static (0, 0) to all
  init_sum();
  dsum = 0;
  dp = fsum;
  //PR(dp);
  for (auto y: ys) {
    if (y != 0) {
      for (auto z: ym[y]) {
        char dd = z.second;
        if (dd == 'S') --dp;
      }
      fsum = dp;
    }
    for (auto x: xs) {
      // minus west
      if (x != 0 || y != 0) {
        for (auto z: xm[x]) {
          char dd = z.second;
          if (dd == 'W') --fsum;
        }
      }
      //PR("here");
      //PR(x);
      //PR(y);
      //PR(dsum);
      //PR(fsum);
      //PR(xres);
      //PR(yres);
      if (dsum < fsum) {
        dsum = fsum;
        xres = x;
        yres = y;
      } else if (dsum == fsum) {
        if (x < xres) { xres = x, yres = y; }
        else if (x == xres && y < yres) {
          xres = x, yres = y;
        }
      }
      // add east
      for (auto z: xm[x]) {
        char dd = z.second;
        if (dd == 'E') ++fsum;
      }
    }
    // add N
    for (auto z: ym[y]) {
      if (z.second == 'N') ++dp;
    }
  }
}

void solve() {
  dsum = 0;
  inc (i, 0, Q + 1) {
    inc (j, 0, Q + 1) {
      fsum = 0;
      inc (k, 1, P + 1) {
        if (i < X[k] && D[k] == 'W') ++fsum;
        if (X[k] < i && D[k] == 'E') ++fsum;
        if (j < Y[k] && D[k] == 'S') ++fsum;
        if (Y[k] < j && D[k] == 'N') ++fsum;
      }
      if (dsum < fsum) {
        dsum = fsum;
        xres = i;
        yres = j;
      } else if (dsum == fsum) {
        if (i < xres) { xres = i, yres = j; }
        else if (i == xres && j < yres) { xres = i, yres = j; }
      }
    }
  }
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
    scanf("%d %d", &P, &Q);
    inc (j, 1, P + 1) scanf("%d %d %c", &X[j], &Y[j], &D[j]);
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d %d\n", i, xres, yres);
  }
  return 0;
}

