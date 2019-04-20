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
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define PRM(x) cout << #x << ": " << endl; for (auto& x##_it: x) cout << (x##_it).first << ": " << (x##_it).second << endl; cout << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 5001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, M;
ll F[LARGE][LARGE];
ll ST[LARGE];
ll DLT[LARGE];
ll DP[LARGE][3];

void init() {
  // cmp N!
  ST[0] = 1 % M;
  inc (i, 1, N + 1) ST[i] = (ST[i - 1] * i) % M;
  //PRA(ST, N + 1);
  // cmp F(n, 1), equal DLT[n]
  inc (i, 1, N + 1) {
    DLT[i] = ST[i];
    inc (j, 1, i)  {
      ll s = (ST[j] * DLT[i - j]) % M;
      if (DLT[i] < s) DLT[i] += M - s;
      else DLT[i] -= s;
    }
  } 
  inc (i, 1, N + 1) F[i][1] = DLT[i];
  //PRA(DLT, N + 1);
}

ll solve() {
  // cmp F(i, j)
  memset(DP, 0, sizeof DP);
  DP[0][0] = 1 % M;
  DP[0][1] = 0;
  DP[0][2] = 0;
  inc (i, 1, N + 1) {
    inc (j, 1, i + 1) {
      DP[i][0] += (DLT[j] * DP[i - j][0]) % M;
      DP[i][0] %= M;
      DP[i][1] += ((DP[i - j][0] + DP[i - j][1]) * DLT[j]) % M;
      DP[i][1] %= M;
      DP[i][2] += ((DP[i - j][0] + 2 * DP[i - j][1] + DP[i - j][2]) * DLT[j]) % M;
      DP[i][2] %= M;
    }
  }
  // detect
  inc (i, 2, N + 1) {
    ll s = 0;
    inc (j, 1, N + 1) {
      //debug("F[%d][%d]: %lld\n", i, j, F[i][j]);
      s += F[i][j];
    }
    //debug("sum is: %lld\n", s);
    //debug("n per is: %lld\n", ST[i]);
  }
  return DP[N][2];
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
    scanf("%lld %lld", &N, &M);
    init();
    ll r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, r);
  }
  return 0;
}

