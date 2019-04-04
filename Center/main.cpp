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

#define LARGE 20001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int N;
ld X[LARGE], Y[LARGE], W[LARGE];
pair<ld, ld> A[LARGE], S[LARGE];

ld C[LARGE];
ld XN[LARGE], YN[LARGE];

ld cmp_init() {
  XN[0] = YN[0] = 0.0;
  ld res = 0.0;
  inc (i, 1, N + 1) {
    res += W[i] * X[i];
    XN[0] -= W[i];
  }
  return res;
}

ld solve() {
  // cmp x + y, x - y for each point
  inc (i, 1, N + 1) A[i] = {X[i] + Y[i], i}, S[i] = {X[i] - Y[i], i};
  sort (A + 1, A + N + 1);
  sort (S + 1, S + N + 1);

  // determinate each A
  ld res = LDBL_MAX;
  ld x, y;
  C[0] = cmp_init();
  inc (i, 1, N + 1) {
    int k = A[i].second;
    // r -> d
    C[0] -= W[k] * X[k];
    XN[0] += W[k];
    C[0] -= W[k] * Y[k];
    YN[0] += W[k];
    inc (j, 1, N + 1) {
      x = (A[i].first + S[j].first) / 2.0;
      y = (A[i].first - S[j].first) / 2.0;
      int kk = S[j].second;
      if (X[kk] + Y[kk] < A[i].first) {
        // d -> l
        C[j] = C[j - 1] + W[kk] * Y[kk] - W[kk] * X[kk];
        YN[j] = YN[j - 1] - W[kk];
        XN[j] = XN[j - 1] + W[kk];
      } else {
        // r -> u
        C[j] = C[j - 1] - W[kk] * X[kk] + W[kk] * Y[kk];
        XN[j] = XN[j - 1] + W[kk];
        YN[j] = YN[j - 1] - W[kk];
      }
      res = min(res, C[j] + XN[j] * x + YN[j] * y);
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
    scanf("%d", &N);
    inc (j, 1, N + 1) scanf("%llf %llf %llf", &X[j], &Y[j], &W[j]);
    ld res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.7llf\n", i, res);
  }
  return 0;
}

