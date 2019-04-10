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
#define PRV(x) cout << #x << ": "; for (auto& x##_it: x) cout << x##_it << ' '; cout << endl;
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
#define MLARGE 10005
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

ll solve() {
  init();
  memset(DP, 0, sizeof DP);
  ll res = 0;
  inc (i, 1, N + 1) {
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

