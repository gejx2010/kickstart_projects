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
#define PRM(x) cout << #x << ": " << endl; for (auto& x##_it: x) cout << (x##_it).first << ": " << (x##_it).second << endl; cout << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
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
int R, C, RS, CS, S;
ld P, Q;
char gram[LARGE][LARGE];
ld vgr[LARGE][LARGE];
map<pri, int> route;
ld fres, cres;

vector<pri> dtn(pri d) {
  int x = d.first, y = d.second;
  vector<pri> s;
  if (1 < x) s.pb({x - 1, y});
  if (x < R) s.pb({x + 1, y});
  if (1 < y) s.pb({x, y - 1});
  if (y < C) s.pb({x, y + 1});
  return s;
}

void try_insert(pri dr) {
  if (route.count(dr)) ++route[dr];
  else route[dr] = 1;
}

void try_delete(pri dr) {
  if (route[dr] == 1) route.erase(dr);
  else --route[dr];
}

ld cnt_value(pri dr) {
  int x = dr.first, y = dr.second;
  int n = route[dr];
  ld r = 1.0;
  inc (i, 1, n) r *= (1 - vgr[x][y]);
  r *= vgr[x][y];
  return r;
}

void travel(pri dr, int st) {
  if (st == S) {
    //PR("finish route");
    for (auto v: route) {
      auto p = v.first;
      int n = v.second;
      int x = p.first, y = p.second;
      //PR(x);
      //PR(y);
      //PR(n);
    }
    //PR(cres);
    fres = max(fres, cres);
    return;
  }
  for (auto d: dtn(dr)) {
    try_insert(d);
    ld v = cnt_value(d);
    cres += v;
    travel(d, st + 1);
    cres -= v;
    try_delete(d);
  }
}

ld solve() {
  memset(vgr, 0, sizeof vgr);
  inc (i, 1, R + 1) inc (j, 1, C + 1) {
    if (gram[i][j] == '.') vgr[i][j] = Q;
    else vgr[i][j] = P;
    //PR(i);
    //PR(j);
    //PR(vgr[i][j]);
  }
  fres = cres = 0.0;
  travel({RS + 1, CS + 1}, 0);
  return fres;
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
    cin >> R >> C >> RS >> CS >> S;
    cin >> P >> Q;
    inc (j, 1, R + 1) inc (k, 1, C + 1) cin >> gram[j][k];
    ld r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.9llf\n", i, r);
  }
  return 0;
}

