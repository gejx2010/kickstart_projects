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
typedef vector<pri> vpri;
typedef vector<pri> vtpi;

using prd = pair<double,double>;

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 500
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int R, C;
char S[LARGE][LARGE];
int mark[LARGE][LARGE];
vpri vp, nvp;
vi uvi, dvi;

int solve1() {
  vp.clear();
  rep(i, 1, R + 1) rep(j, 1, C + 1) if (S[i][j] == '1') vp.pb({i, j});
  if (vp.size() == R * C) return 0;
  //for (auto n: vp) debug("(f, s): (%d, %d)\n", n.first, n.second);
  int res = INT_MAX;
  rep(i, 1, R + 1) rep(j, 1, C + 1) if (S[i][j] == '0') {
    vp.pb({i, j});
    S[i][j] = '1';
    //debug("(i, j): (%d, %d)\n", i, j);
    int dis = 0;
    rep(m, 1, R + 1) rep(n, 1, C + 1) if (S[m][n] == '0') {
      //debug("(m, n): (%d, %d)\n", m, n);
      int cdis = INT_MAX;
      for (auto p: vp) {
        int l = p.first, r = p.second;
        //debug("(l, r): (%d, %d)\n", l, r);
        cdis = min(cdis, abs(l - m) + abs(r - n));
      }
      //PR(cdis);
      dis = max(dis, cdis); 
      //PR(dis);
    }
    res = min(res, dis);
    //PR(res);
    vp.pop_back();
    S[i][j] = '0';
  }
  return res;
}

void inter(vpri vp) {
  memset(mark, -1, sizeof mark);
  vpri c;
  int dp = 0;
  while (!vp.empty()) {
    for (auto p: vp) {
      int x = p.first, y = p.second;
      if (mark[x][y] < 0) mark[x][y] = dp;
      else continue;
      if (1 < x) c.pb(mp(x - 1, y));
      if (x < R) c.pb(mp(x + 1, y)); 
      if (1 < y) c.pb(mp(x, y - 1));
      if (y < C) c.pb(mp(x, y + 1));
    }
    ++dp;
    vp = c;
    c.clear();
  }
}

bool fit(int k) {
  // find mark >= k
  uvi.clear(), dvi.clear();
  rep (i, 1, R + 1) rep (j, 1, C + 1) if (k < mark[i][j]) {
    uvi.pb(i + j);
    dvi.pb(i - j);
  }
  int usz = uvi.size(), dsz = dvi.size();
  //PR(usz);
  //PR(dsz);
  if (usz < 1 || dsz < 1) return true;
  sort(uvi.begin(), uvi.end());
  sort(dvi.begin(), dvi.end());
  //PR(uvi[0]);
  //PR(uvi[usz - 1]);
  //PR(dvi[0]);
  //PR(dvi[dsz - 1]);

  // check each point of nvp
  for (auto p: nvp) {
    int u = p.first + p.second, d = p.first - p.second;
    //PR(u);
    //PR(d);
    if (abs(uvi[0] - u) <= k && abs(uvi[usz - 1] - u) <= k
       && abs(dvi[0] - d) <= k && abs(dvi[dsz - 1] - d) <= k) return true;
  } 
  return false;
}

int solve() {
  vp.clear(), nvp.clear();
  rep (i, 1, R + 1) rep (j, 1, C + 1) 
    if (S[i][j] == '1') vp.pb(mp(i, j));
    else nvp.pb(mp(i, j));

  inter(vp);
  int mx = 0;
  rep (i, 1, R + 1) rep (j, 1, C + 1) { 
    //debug("mark[%d][%d]: %d\n", i, j, mark[i][j]);
    mx = max(mx, mark[i][j]);
  }
 
  int d = 0, u = mx, m = 0;
  while (d < u) {
    m = (d + u) >> 1;
    //debug("try fit: %d\n", m);
    bool can_fit = fit(m);
    //debug("fit return: %d\n", can_fit);
    if (can_fit) u = m;
    else d = m + 1;
  }
  return d;
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
    inc(j, 1, R + 1) scanf("%s", S[j] + 1);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

