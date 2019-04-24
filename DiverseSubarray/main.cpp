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

#define LARGE 200001
#define COMPILE false
#define TESTTIME false
#define MOD 1000000007

// define initial parameters here
int T = 0;
int N, S;
int A[LARGE];
int sum;
int arr[LARGE];
queue<int> pos[LARGE];

int solve2() {
  memset(arr, 0, sizeof arr);
  inc (i, 1, N + 1) while(!pos[i].empty()) pos[i].pop();
  sum = 0;
  int res = 0, st = 1;
  inc (i, 1, N + 1) {
    int n = A[i];
    if (arr[n] < S) {
      ++arr[n];
      pos[n].push(i);
      ++sum;
      res = max(res, sum);
    } else if (arr[n] == S) {
      int p = pos[n].front();
      if (sum - S < i - p) {
        while (st <= p) {
          int m = A[st];
          --arr[m];
          pos[m].pop();
          ++st;
        }
        sum = i - p;
      } else {
        sum -= S;
        ++arr[n];
        pos[n].push(i);
      }
    } else {
      ++arr[n];
      pos[n].push(i);
    }
  }
  return res;
}

int solve3() {
  int res = 0;
  inc (i, 1, N + 1) {
    memset(arr, 0, sizeof arr);
    sum = 0;
    inc (j, i, N + 1) {
      int n = A[j];
      ++arr[n];
      if (arr[n] <= S) { ++sum; res = max(res, sum); }
      else if (arr[n] == S + 1) sum -= S;
    }
  }
  return res;
}

int solve() {
  memset(arr, 0, sizeof arr);
  sum = 0;
  inc (i, 1, N + 1) {
    int n = A[i];
    ++arr[n];
    if (arr[n] <= S) ++sum;
    else if (arr[n] == S + 1) sum -= S;
  }
  int res = 0;
  int st = 1, ed = N;
  res = max(res, sum);
  while (st <= ed) {
    int ls = sum;
    int ln = A[st];
    if (arr[ln] <= S) --ls;
    else if (arr[ln] == S + 1) ls += S;
    int rs = sum;
    int rn = A[ed];
    if (arr[rn] <= S) --rs;
    else if (arr[rn] == S + 1) rs += S;
    if (ls < rs) {
      --ed;
      sum = rs;
      --arr[rn];
      res = max(res, sum);
    } else {
      ++st;
      sum = ls;
      --arr[ln];
      res = max(res, sum);
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
    cin >> N >> S;
    inc (i, 1, N + 1) cin >> A[i];
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

