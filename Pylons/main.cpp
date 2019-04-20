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
#define rep(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 21
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int R, C;
vector<pri> path;
set<pri> spa;

// solve 2
set<pri> full[LARGE][LARGE];
bool mark[LARGE][LARGE];
set<pri> npath;
bool fin_res;

bool cft(int a, int b, int c, int d) {
  if (a == c) return true;
  if (b == d) return true;
  if (a - b == c - d) return true;
  if (a + b == c + d) return true;
  return false;
}

bool travel(int l, int r) {
  path.pb({l, r});
  spa.insert({l, r});
  if (path.size() == R * C) return true;
  inc (i, 1, R + 1) inc (j, 1, C + 1) if (!spa.count({i, j})) {
    if (!cft(i, j, l, r)) {
      //PR(l);
      //PR(r);
      //PR(i);
      //PR(j);
      if (travel(i, j)) return true;
      else return false;
    }
  }
  return false;
}

bool solve2() {
  path.clear();
  spa.clear();
  return travel(1, 1);
}

void cnt_sel() {
  npath.clear();
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    if (!mark[i][j]) {
      if (full[i][j].empty()) { fin_res = false; return; }
      if (full[i][j].size() == 1) npath.insert({i, j});
    }
  }
  if (2 < npath.size()) fin_res = false;
}

void try_del(pri cp) {
  inc (i, 1, R + 1) inc (j, 1, C + 1) 
    full[i][j].erase(cp);
}

pri sel_one(pri cp) {
  if (full[cp.first][cp.second].empty()) {
    fin_res = false;
    return {0, 0};
  }
  auto it = full[cp.first][cp.second].begin();
  return *it;
}

bool solve() {
  memset(mark, 0, sizeof mark);
  fin_res = true;
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    full[i][j].clear();
    inc (k, 1, R + 1) inc (m, 1, C + 1) 
      if (!cft(i, j, k, m)) full[i][j].insert({k, m});
  }

  pri cp = {1, 1};
  mark[1][1] = true;
  path.pb(cp);
  try_del(cp);
  while (path.size() < R * C) {
    //PR(cp.first);
    //PR(cp.second);
    cnt_sel();
    if (!fin_res) return false;
    if (npath.size() < 2) {
      cp = sel_one(cp);
      path.pb({cp.first, cp.second});
      mark[cp.first][cp.second] = true;
      try_del(cp);
      continue;
    }
    bool can_sel = false;
    for (auto v: npath) {
      int x = v.first, y = v.second;
      if (!cft(cp.first, cp.second, x, y)) {
        cp = v;
        can_sel = true;
        path.pb({x, y});
        mark[x][y] = true;
        try_del(cp);
        break;
      }
    }
    if (!can_sel) return false;
  }
  if (!fin_res) return false;
  return true;
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
    cin >> R >> C;
    bool r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (r) {
      printf("Case #%d: POSSIBLE\n", i);
      for (auto v: path) printf ("%d %d\n", v.first, v.second);
    } else {
      printf("Case #%d: IMPOSSIBLE\n", i);
    }
  }
  return 0;
}

