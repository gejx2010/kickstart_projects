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
#define PRA(x,sz) cout << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cout << (x)[x##_it] << " "; cout << endl;
#define PRV(x) cout << #x << ": "; for (auto& x##_it: x) cout << x##_it << ' '; cout << endl;
#define PRM(x) cout << #x << ": "; for (auto& x##_it: x) cout << (x##_it).first << ": " << (x##_it).second << endl; cout << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b + 0) i = a, i##_end_ = b; i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 201
#define COM 8
#define MLARGE 10005
#define GLARGE 1000005
#define SMALL 20
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll M, N;
ll K[LARGE], L[LARGE];
ll A[LARGE][LARGE];
ll C[LARGE][LARGE];
ll DC[LARGE][LARGE];
vector<ll> vp;
ll cc, ca;

// solve2
ll DP[SMALL][MLARGE];

// solve3
map<ll, ll> DMA;
map<ll, ll> DMB;
map<ll, ll> DMC;
map<ll, ll> DMM[SMALL][SMALL][SMALL];

// solve4
ll mask[COM << 1];
prl AMA[GLARGE];
prl AMB[GLARGE];
prl AMC[GLARGE];
ll AMAZ, AMBZ;

void init() {
  inc (i, 1, N + 1) {
    DC[i][L[i]] = 0;
    inc (j, L[i] + 1, K[i] + 1) {
      DC[i][j] = DC[i][j - 1] + C[i][j - 1];
    }
  }
}

ll select() {
  ll rv = 0, ra = 0;
  inc (i, 1, N + 1) {
    rv += DC[i][vp[i]];
    ra += A[i][vp[i]];
  }
  //PR(rv);
  //PR(ra);
  if (rv <= M) return ra;
  return 0;
}

void tnext() {
  inc (i, 1, N + 1) {
    if (vp[i] < K[i] && cc < M) {
      cc += C[i][vp[i]];
      ca += A[i][vp[i] + 1] - A[i][vp[i]];
      ++vp[i];
      break;
    } else {
      cc -= DC[i][vp[i]];
      ca -= A[i][vp[i]] - A[i][L[i]];
      vp[i] = L[i];
    }
  }
}

bool finish() {
  inc (i, 1, N + 1) if (vp[i] != L[i]) return false;
  return true;
}

ll solve2() {
  init();
  vp.clear();
  vp.pb(0);
  inc (i, 1, N + 1) vp.pb(L[i]);
  ll r = select();
  cc = 0, ca = r;
  //PR(r);
  tnext();
  while (!finish()) {
    //PRV(vp);
    if (cc <= M) r = max(r, ca);
    tnext();
  }
  return r;
}

ll solve3() {
  init();
  memset(DP, 0, sizeof DP);
  ll res = 0;
  inc (i, 1, N + 1) {
    DP[i][0] = max(DP[i - 1][0], A[i][L[i]]);
    inc (j, 1, MLARGE - 1) {
      DP[i][j] = max(DP[i][j], DP[i][j - 1]); 
      inc (k, L[i], K[i] + 1) {
        if (DC[i][k] <= j) DP[i][j] = max(DP[i][j], A[i][k] + DP[i - 1][j - DC[i][k]]);
      }
      //debug("DP[%d][%d]: %lld\n", i, j, DP[i][j]);
      if (j <= M) res = max(res, DP[i][j]);
    }
  }
  return res;
}

void try_insert(map<ll, ll>& m, ll k, ll v) {
  if (M < k) return;
  if (!m.count(k)) m[k] = v;
  else m[k] = max(m[k], v);
}

void get_before(map<ll, ll>& m) {
  ll bf = 0;
  for (auto u: m) {
    ll c = u.first, a = u.second;
    m[c] = max(a, bf);
    bf = m[c];
  }
}

map<ll, ll> merge(map<ll, ll>& ma, map<ll,ll>& mb) {
  if (ma.empty()) return mb;
  if (mb.empty()) return ma;
  // merge a + b
  map<ll, ll> m;
  for (auto u: ma) {
    ll c = u.first, a = u.second;
    for (auto v: mb) {
      ll vc = v.first, va = v.second;
      try_insert(m, vc + c, va + a);
    }
  }
  // get before to next
  get_before(m);
  return m;
}

map<ll, ll> mgs(ll st, ll ed, ll n) {
  //debug("mgs (start, ed, n): (%lld, %lld, %lld)\n", st, ed, n);
  map<ll, ll> m;
  if (n == 0) {
    return m;
  }
  if (n == 1) {
    inc (i, st, ed + 1) 
      inc (j, L[i], K[i] + 1) 
        try_insert(m, DC[mask[i]][j], A[mask[i]][j]);
    //debug("case n is 1.\n");
    //PRM(m);
    return m;
  }
  ll md = (st + ed) >> 1;
  ll lb = md - st + 1, rb = ed - md;
  inc (i, 0, lb + 1) { 
    if (n - i < 0) continue;
    if (rb < n - i) continue;
    auto ma = mgs(st, md, i);
    auto mb = mgs(md + 1, ed, n - i);
    //debug("case n is not 1.\n");
    map<ll, ll> cm = merge(ma, mb);
    //PRM(cm);
    for (auto u: cm) 
      try_insert(m, u.first, u.second);
  }
  get_before(m);
  return m;
}

ll solve4() {
  init();
  // clear dmm
  inc (i, 1, SMALL) inc (j, 1, SMALL) inc(k, 1, SMALL) DMM[i][j][k].clear();
  ll m = (1 + N) >> 1; 
  ll r = 0;
  inc (i, COM - (N - m), m + 1) {
    DMA.clear();
    DMB.clear();
    DMA = mgs(1, m, i);
    DMB = mgs(m + 1, N, COM - i);
    for (auto u: DMA) {
      ll c = u.first, a = u.second;
      auto it = DMB.upper_bound(M - c);
      --it;
      r = max(r, a + it->second);
    }
  }
  return r;
}

bool detect(ll n) {
  int rk = 0, cr = 1;
  while (n) {
    if (n & 1) mask[++rk] = cr;
    n >>= 1;
    ++cr;
  }
  if (rk == COM) return true;
  return false;
}

void swap(prl* ar, ll f, ll g) {
  auto m = ar[f];
  ar[f] = ar[g];
  ar[g] = m;
}

void sort_dup(prl* ar, ll& arz, ll st, ll ed) {
  sort(ar + st, ar + ed);
  ll bc = ar[st].first, bv = ar[st].second;
  ll rk = st;
  inc (i, st, ed) {
    ll c = ar[i].first;
    if (c != bc) {
      if (rk != i - 1) 
        std::swap(ar[rk], ar[i - 1]);
      ar[rk].second = max(ar[rk].second, bv);
      bv = ar[rk].second;
      ++rk;
    }
    bc = c;
  }
  std::swap(ar[rk], ar[ed - 1]);
  ar[rk].second = max(ar[rk].second, bv);
  arz = rk + 1 - st;
}

void merge(prl* ar, ll& arz, ll f, ll fz, ll g, ll gz) {
  ll sz = 0;
  inc (i, f, f + fz) inc (j, g, g + gz) {
    if (ar[i].first + ar[j].first <= M) AMC[sz++] = {ar[i].first + ar[j].first, ar[i].second + ar[j].second};
  }
  inc (i, f, f + sz) ar[i] = AMC[i - f];
  // sort & duplicate
  sort_dup(ar, arz, f, f + sz); 
}

void mgss(ll st, ll ed, ll n, prl* ar, ll& arz, ll ast, ll aed) {
  //debug("mgs (start, ed, n): (%lld, %lld, %lld)\n", st, ed, n);
  //PR(ast);
  //PR(aed);
  if (n == 0) {
    return;
  }
  if (n == 1) {
    ll f = ast;
    inc (i, st, ed + 1) {
      inc (j, L[mask[i]], K[mask[i]] + 1) {
        if (DC[mask[i]][j] <= M) ar[f++] = {DC[mask[i]][j], A[mask[i]][j]};
      }
    }
    sort_dup(ar, arz, ast, f);
    //inc (i, ast, f) debug("ar[%d]: (%d, %d)\n", i, ar[i].first, ar[i].second);
    return;
  }
  ll md = (st + ed) >> 1;
  ll lb = md - st + 1, rb = ed - md;
  ll mv = (ast + aed) >> 1;
  ll maz = 0, mbz = 0;
  mgss(st, md, lb, ar, maz, ast, mv);
  mgss(md + 1, ed, rb, ar, mbz, mv, aed);
  merge(ar, arz, ast, maz, mv, mbz);
  //inc (i, ast, ast + arz) debug("ar[%d]: (%d, %d)\n", i, ar[i].first, ar[i].second);
  return;
}

ll solve() {
  init();
  ll m = COM >> 1; 
  ll r = 0;
  ll ini = (1 << COM) - 1;
  ll last = (((1 << COM) - 1) << (N - COM)) + 1;
  ll cnt = 0;
  inc (i, ini, last) {
    if (!detect(i)) continue;
    AMAZ = 0;
    AMBZ = 0;
    mgss(1, m, m, AMA, AMAZ, 0, GLARGE - 1);
    mgss(m + 1, COM, COM - m, AMB, AMBZ, 0, GLARGE - 1);
    inc (j, 0, AMAZ) {
      ll c = AMA[j].first, a = AMA[j].second;
      prl k = {M - c, LLONG_MAX};
      auto it = upper_bound(AMB, AMB + AMBZ, k);
      --it;
      if (AMB + AMBZ <= it) PR("wrong index");
      r = max(r, a + it->second);
    }
  }
  return r;
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
    //init
    memset(A, 0, sizeof A);
    memset(C, 0, sizeof C);
    memset(K, 0, sizeof K);
    memset(L, 0, sizeof L);
    scanf("%lld %lld", &M, &N);
    inc (j, 1, N + 1) {
      scanf("%lld %lld", &K[j], &L[j]);
      inc (k, 1, K[j] + 1) scanf("%lld", &A[j][k]);
      inc (k, 1, K[j]) scanf("%lld", &C[j][k]);
    }
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

