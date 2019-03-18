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
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 2001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, TS, TF;
ll S[LARGE], F[LARGE], D[LARGE];
ll DP[LARGE][LARGE];

ll find_time(ll st, int rk) {
  if (st <= S[rk]) return S[rk] + D[rk];
  ll lv = st - S[rk];
  ll trk = lv / F[rk];
  return (st == S[rk] + trk * F[rk]) ? st + D[rk] : S[rk] + (trk + 1) * F[rk] + D[rk]; 
}

int solve() {
  memset(DP, 0, sizeof DP);
  rep (i, 1, N) {
    DP[i][0] = find_time(DP[i - 1][0], i);
    DP[i - 1][i] = INT_MAX;
    rep (j, 1, i + 1) {
      DP[i][j] = min(find_time(DP[i - 1][j], i), find_time(DP[i - 1][j - 1] + TS, i));
    }
  }
  for (int i = N - 1; 0 <= i; --i) if (DP[N - 1][i] <= TF) {
    return i;
  }
  return -1;
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
    scanf("%lld %lld %lld", &N, &TS, &TF);
    rep(j,1,N) scanf("%lld %lld %lld", &S[j], &F[j], &D[j]);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (0 <= res) printf("Case #%d: %d\n", i, res);
    else printf("Case #%d: IMPOSSIBLE\n", i);
  }
  return 0;
}

