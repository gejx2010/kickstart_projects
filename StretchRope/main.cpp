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

#define LARGE 1001
#define MLARGE 10001
#define COMPILE false
#define TESTTIME true
#define MOD 1000000007

// define initial parameters here
int T = 0;
int N, M, L;
int A[LARGE], B[LARGE], P[LARGE];
int bmk;

int solve2() {
  int res = INT_MAX;
  inc (i, 1, 1 << N) {
    int cl = 0, cr = 0, cp = 0;
    int k = 1;
    inc (j, 1, N + 1) {
      if (i & k) {
        cl += A[j];
        cr += B[j];
        cp += P[j];
      }
      k <<= 1;
    }
    if (cl <= L && L <= cr && cp <= M) res = min(res, cp);
  }
  return res;
}

int DP[LARGE][MLARGE];
multiset<int> cm;

void try_erase(int v) {
  auto it = cm.lower_bound(v);
  cm.erase(it);
}

int solve() {
  memset(DP, 0, sizeof DP);
  inc (i, 1, N + 1) {
    cm.clear();
    inc (j, 1, L + 1) {
      if (A[i] < j) {
        if (0 < DP[i - 1][j - A[i]]) cm.insert(DP[i - 1][j - A[i]]);
        if (B[i] < j - 1) {
          if (0 < DP[i - 1][j - B[i] - 1]) try_erase(DP[i - 1][j - B[i] - 1]);
        }
        if (j <= B[i]) DP[i][j] = P[i];
        if (!cm.empty()) {
          auto v = (*cm.begin()) + P[i];
          if (DP[i][j]) DP[i][j] = min(DP[i][j], v);
          else DP[i][j] = v;
        }
        if (DP[i - 1][j]) {
          if (DP[i][j]) DP[i][j] = min(DP[i][j], DP[i - 1][j]);
          else DP[i][j] = DP[i - 1][j];
        }
      } else if (j == A[i]) {
        if (DP[i - 1][j]) DP[i][j] = min(P[i], DP[i - 1][j]);
        else DP[i][j] = P[i];
      } else {
        DP[i][j] = DP[i - 1][j];
      }
    }
  }
  return DP[N][L];
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
    cin >> N >> M >> L;
    inc (j, 1, N + 1) cin >> A[j] >> B[j] >> P[j];
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (r && r <= M) printf("Case #%d: %d\n", i, r);
    else printf("Case #%d: IMPOSSIBLE\n", i);
  }
  return 0;
}

