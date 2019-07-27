/***************************************
Author: spgoal
Date: Wed, May/26/2019, 18:51:03
Lang: C++
***************************************/

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
#define rep(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype((b) + 0) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype((a) + 0) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)
#define lch(x) ((x) << 1)
#define rch(x) (((x) << 1) + 1)

#define LARGE 1001
#define COMPILE false
#define TESTTIME false
#define MOD 1000000007

// define initial parameters here
int T = 0;
int R, C, K;
int V[LARGE][LARGE];
int S[LARGE][LARGE];

void init() {
  memset(S, 0, sizeof S);
  inc (i, 1, R + 1) {
    inc (j, 1, C + 1) {
      S[i][j] = 1;
      int mn = V[i][j], mx = V[i][j];
      inc (k, j + 1, C + 1) {
        mn = min(mn, V[i][k]);
        mx = max(mx, V[i][k]);
        if (K < mx - mn) break;
        ++S[i][j];
      }
    }
  }
}

int solve() {
  init();
  int ans = 0;
  inc (i, 1, R + 1) {
    inc (j, 1, C + 1) {
      int mx = 0, mc = INT_MAX;
      inc (k, i, R + 1) {
        mc = min(mc, S[k][j]);
        mx = max(mx, (k - i + 1) * mc);
      }
      ans = max(ans, mx);
    }
  }
  return ans;
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
    cin >> R >> C >> K;
    inc (j, 1, R + 1) inc (k, 1, C + 1) cin >> V[j][k];
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

