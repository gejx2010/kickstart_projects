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

#define LARGE 2000001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int mmax, mmin, mean, mmed;
int A[LARGE];
int cnt;

bool fit() {
  PR(A[0]);
  PR(A[1]);
  sort(A, A + cnt);
  if (mmin != A[0]) return false;
  if (mmax != A[cnt - 1]) return false;
  int s = 0;
  inc (i, 0, cnt) s += A[i];
  if (s != cnt * mean) return false; 
  if (cnt & 1) return (mmed == A[cnt / 2]);
  return ((mmed << 1) == (A[cnt / 2] + A[cnt / 2 - 1]));
}

int test_diff(int diff) {
  int ld = mmin + mmed, rd = mmax + mmed, md = 2 * mean;
  if (0 < diff) {
    if (rd <= md) return INT_MAX;
    if (md + diff < ld) return INT_MAX;
    inc (i, 1, LARGE) {
      cnt += 2;
      if (ld <= md + diff && md + diff <= rd) 
        return cnt;
      diff += (md - rd);
    }
  } else {
    if (md <= ld) return INT_MAX;
    if (rd < md + diff) return INT_MAX;
    inc (i, 1, LARGE) {
      cnt += 2;
      if (ld <= md + diff && md + diff <= rd) return cnt;
      diff += (md - ld);
    }
  }
  return INT_MAX;
}

int test_odd() {
  cnt = 2;
  A[cnt++] = mmed;
  if (fit()) return cnt;
  int l = mmin + mmax + mmed, r = 3 * mean;
  return test_diff(r - l);
}

int test_even() {
  int l = mmin + mmax + (mmed << 1), r = (mean << 2);
  cnt = 4;
  if (l == r) return cnt;
  return test_diff(r - l);
}

int solve() {
  PR(mmax);
  PR(mmin);
  PR(mean);
  PR(mmed);
  if (mmax < mmin) return 0;
  if (mean < mmin || mmax < mean) return 0;
  if (mmed < mmin || mmax < mmed) return 0;
  if (mmin == mmax && mmed != mmin) return 0;
  if (mmin == mmax && mean != mmin) return 0;
  if (mean == mmin && mmin != mmax) return 0;
  if (mean == mmax && mmin != mmax) return 0;
  cnt = 0;
  A[cnt++] = mmin;
  if (fit()) return cnt;
  A[cnt++] = mmax;
  if (fit()) return cnt;
  int n1 = test_odd();
  int n2 = test_even();
  int n = min(n1, n2);
  if (n == INT_MAX) return 0;
  return n;
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
    scanf("%d %d %d %d", &mmin, &mmax, &mean, &mmed);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    if (0 < res) printf("Case #%d: %d\n", i, res);
    else printf("Case #%d: IMPOSSIBLE\n", i);
  }
  return 0;
}

