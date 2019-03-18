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

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (decltype(sz) x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 201
#define COMPILE false
#define TESTTIME true
#define EPSILON 1e-7
#define ELARGE 100000

// define initial parameters here
int T = 0;
ll N, M, P;
ll L[LARGE][LARGE];
ll DS[LARGE][LARGE];
ll dis[LARGE];

void compute_distance(int rk) {
  memset(dis, 0, sizeof dis);
  set<int> v = {rk};
  set<int> nv = {};
  rep(i,1,N+1) if (i != rk) {
    nv.insert(i);
    if (L[rk][i]) dis[i] = L[rk][i];
  }
  while (!nv.empty()) {
    // select min
    int mk = 0;
    ll cmin = LLONG_MAX;
    for (auto i: nv) 
      if (0 < dis[i] && dis[i] < cmin) {
        mk = i;
        cmin = dis[i];
      }
    // add and update
    DS[rk][mk] = cmin;
    v.insert(mk);
    nv.erase(mk);
    rep(i,1,N+1) if (nv.count(i) && L[mk][i]) 
      dis[i] = (dis[i] == 0) ? dis[mk] + L[mk][i] : min(dis[i], dis[mk] + L[mk][i]);
  }
}

ld cmp_step(ld a, ll k, ld bias) {
  ld res = a * bias;
  rep(i,1,k) {
    res *= a;
    if (fabs(res) < EPSILON) break;
  }
  return res;
}

ld solve() {
  if (N == 2) return (ld)L[1][2] * P;

  memset(DS, 0, sizeof(DS));
  rep(i,1,N+1) compute_distance(i);
  ld fs = 0.0;
  rep(i,2,N+1) fs += DS[1][i];
  PR(fs);
  ld dfs = fs / (N - 1);
  if (P == 1) return dfs;

  ld sc = 0.0;
  rep(i,2,N+1) rep(j,1,N+1) if (i != j) sc += DS[i][j];
  PR(sc);
  ld dsc = sc / ((N - 1) * (N - 1));
  if (P == 2) return dfs + dsc;

  ld p1 = sc * (ld) P / (N * (N - 1)) - sc / (N * N);
  PR(p1);
  ld k1 = cmp_step((ld)(-1.0) / (N - 1), P, sc / (N * N));
  PR(k1);
  PR(p1 + k1);
  ld p2 = P * fs / (N * (N - 1)) + (N - 1) * fs / (N * N);
  PR(p2);
  ld k2 = cmp_step((ld)(-1.0) / (N - 1), P, (N - 1) * fs / (N * N));
  PR(k2);
  PR(p2 + k2);
  return p1 + k1 + p2 - k2;
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
    scanf("%lld %lld %lld", &N, &M, &P);
    memset(L, 0, sizeof L);
    ll a, b, c;
    rep(j,0,M) {
      scanf("%lld %lld %lld", &a, &b, &c);
      L[a][b] = c;
      L[b][a] = c;
    }
    ld res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.7llf\n", i, res);
  }
  return 0;
}

