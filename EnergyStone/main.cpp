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

#define SMALL 101
#define MIDDLE 10001
#define LARGE 100001
#define COMPILE false
#define TESTTIME false
#define MOD 1000000007

// define initial parameters here
int T = 0;
int N;
int S[LARGE], E[LARGE], L[LARGE];
tuple<double,int,int,int> tn[LARGE];
int DP[SMALL][MIDDLE];

ll solve() {
  inc (i, 1, N + 1) {
    if (L[i] == 0) tn[i] = mt((double)INT_MAX, -L[i], S[i], E[i]);
    else tn[i] = mt((double)S[i] / L[i], -L[i], S[i], E[i]);
  }
  sort(tn + 1, tn + N + 1);
  memset(DP, 0, sizeof DP);
  inc (i, 1, N + 1) {
    double f;
    int l, e, s;
    tie(f, l, s, e) = tn[i];
    l = -l;
    inc (j, 1, MIDDLE) {
      int t = j - s;
      ll las = (ll)l * t;
      ll lev = (ll)e - las;
      int et = (0 <= t && 0 < lev) ? DP[i - 1][t] + lev : 0;
      int net = DP[i - 1][j];
      int bf = DP[i][j - 1];
      DP[i][j] = max(et, max(net, bf));
    }
  }
  return DP[N][MIDDLE - 1];
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
    cin >> N;
    inc (j, 1, N + 1) cin >> S[j] >> E[j] >> L[j];
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

