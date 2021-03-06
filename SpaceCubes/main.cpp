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

#define LARGE 2005
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N;
ll X[LARGE], Y[LARGE], Z[LARGE], R[LARGE];
ll bd[4][3];

ll cmp_dis(ll lb, ll* a, int rk) {
  ll l = abs(a[rk] + R[rk] - lb);
  ll r = abs(a[rk] - R[rk] - lb);
  ll lmx = max(l, r);
  return lmx;
}

ll loop(tpl a, tpl b) {
  ll ax, ay, az, bx, by, bz;
  tie(ax, ay, az) = a;
  tie(bx, by, bz) = b;
  ll mx, my, mz;
  ll res = 0;
  inc (i, 1, N + 1) {
    mx = cmp_dis(ax, X, i);
    my = cmp_dis(ay, Y, i);
    mz = cmp_dis(az, Z, i);
    ll lr = max(mx, max(my, mz));
    mx = cmp_dis(bx, X, i);
    my = cmp_dis(by, Y, i);
    mz = cmp_dis(bz, Z, i);
    ll rr = max(mx, max(my, mz));
    res = max(res, min(lr, rr));
  }
  return res;
}

ll solve() {
  // find boundary
  inc (i, 1, 4) inc (j, 1, 3) {
    if (j == 1) bd[i][j] = INT_MAX;
    else bd[i][j] = INT_MIN;
  }
  inc (i, 1, N + 1) {
    bd[1][1] = min(bd[1][1], X[i] - R[i]);
    bd[1][2] = max(bd[1][2], X[i] + R[i]);
    bd[2][1] = min(bd[2][1], Y[i] - R[i]);
    bd[2][2] = max(bd[2][2], Y[i] + R[i]);
    bd[3][1] = min(bd[3][1], Z[i] - R[i]);
    bd[3][2] = max(bd[3][2], Z[i] + R[i]);
  }
  ll res = INT_MAX;
  inc (i, 1, 3) inc (j, 1, 3) {
    res = min(res, 
              loop(mt(bd[1][1], bd[2][i], bd[3][j]),
                   mt(bd[1][2], bd[2][3 - i], bd[3][3 - j])));
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
    inc (j, 1, N + 1) cin >> X[j] >> Y[j] >> Z[j] >> R[j];
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

