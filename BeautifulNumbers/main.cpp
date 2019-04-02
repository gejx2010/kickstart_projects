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
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 64
#define NLARGE (((ll)1) << 60)
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll sa[LARGE][LARGE];
int ml;

void precmp() {
  inc (i, 2, LARGE) {
    sa[0][i] = 1;
    ll c = i;
    inc (j, 1, LARGE) {
      sa[j][i] = sa[j - 1][i] + c; 
      c *= i;
      if (NLARGE < sa[j][i] || sa[j][i] < sa[j - 1][i]) {
        sa[j][i] = 0;
        if (i == LARGE - 1) ml = j;
        break;
      }
    }
  }
}

ll cmp_step(ll a, ll k) {
  ll s = 0;
  ll cs = 1;
  ll t = 1;
  ll bt = 1;
  inc (i, 1, k) {
    t *= a;
    if (t / a != bt) return LLONG_MAX;
    cs += t;
    if (NLARGE < cs || cs < s || cs < t) return LLONG_MAX;
    s = cs;
    bt = t;
  }
  return cs;
}

ll match(ll n, ll k) {
  ll d = 2, u = INT_MAX;
  while (d < u) {
    ll m = (d + u) >> 1;
    ll r = cmp_step(m, k);
    //PR(m);
    //PR(k);
    //PR(r);
    if (r < n) d = m + 1;
    else if (n < r) u = m;
    else {
      //PR(m);
      //PR(k);
      //PR(r);
      return m;
    }
  }
  return 0;
}

ll solve(ll n) {
  // check list
  //dec (i, LARGE - 1, ml) 
  //  inc (j, 2, LARGE) {
  //    PR(i);
  //    PR(j);
  //    PR(sa[i][j]);
  //    if (sa[i][j] == n) return i + 1;
  //  }

  // search leave
  //PR(n);
  ll m = 0;
  dec (i, LARGE, 3) if (m = match(n, i)) return m;
  return n - 1;
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  scanf("%d", &T);
  precmp();
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    ll N;
    scanf("%lld", &N);
    ll res = solve(N);
    //PR(res);
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

