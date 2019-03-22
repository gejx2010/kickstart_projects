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
#define gel(x,i) get<(i)>(x)

#define LARGE 20
#define COMPILE false
#define TESTTIME false
#define THS 1e-9

// define initial parameters here
int T = 0;
int N, P, H;
int X[LARGE], Y[LARGE];
pair<double,int> O[LARGE];
double M;

double rdis(prd a, prd b) {
  return sqrt((a.first - b.first) * (a.first - b.first)
            + (a.second - b.second) * (a.second - b.second));
}

double cmp_diff(prd v, double A, double x) {
  double a = v.first, b = v.second;
  return 2 * (x - a) + 
         2 * (A * x * (x - P) - b) * (2 * A * x - A * P);
        
}

double cmp_pdis(int rk, double a) {
  if (rk == 0) return (double)H + a * P * P / 4.0;
  double u, d, m;
  if (X[rk] < M) d = 0.0, u = (double) P / 2.0;
  else d = (double)P / 2.0, u = P;
  while (THS < u - d) {
    m = (u + d) / 2;
    if (cmp_diff({X[rk], Y[rk]}, a, m) < 0.0) d = m;
    else u = m;
  }
  return rdis({X[rk], Y[rk]}, {u, a * u * (u - P)});
}

prd dis(double a) {
  pair<double,int> x = {a, 0};
  auto it = lower_bound(O, O + N + 1, x);
  prd res = {H + 1, H + 1};
  inc(i, 0, it - O) res.first = min(res.first, cmp_pdis(O[i].second, a));
  inc(i, it - O, N + 1) res.second = min(res.second, cmp_pdis(O[i].second, a));
  return res;
}

bool exist(double n) {
  double max_dis = 0.0;
  rep(i, 0, N + 1) {
    if (i == N) {
      max_dis = max(max_dis, (double)*min_element(Y, Y + N + 1));
      break;
    }
    double d = O[i].first, u = O[i + 1].first, m = 0.0; 
    while (THS < u - d) {
      m = (u + d) / 2;
      auto v = dis(m);
      if (v.first < v.second) d = m;
      else u = m;
    }
    max_dis = max(max_dis, dis(u).first);
  }
  return n <= max_dis;
}

void cmp_o() {
  O[0] = {- 4.0 * (double)H / ((double)P * P), 0};
  inc(i,1,N+1) O[i] = {(double)Y[i] / ((double)X[i] * (X[i] - P)), i}; 
  O[N + 1] = {0.0, N + 1};
  sort(O, O + N + 1);
}

double solve() {
  cmp_o();
  double d = 0.0, u = H, m = 0.0;
  while (THS < u - d) {
    m = (u + d) / 2;
    if (exist(m)) d = m;
    else u = m;
  }
  return u;
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
    scanf("%d %d %d", &N, &P, &H);
    inc(i,1,N+1) scanf("%d %d", &X[i], &Y[i]);
    M = (double) P / 2;
    X[0] = M, Y[0] = H;
    double res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.7lf\n", i, res);
  }
  return 0;
}

