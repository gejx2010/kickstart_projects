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

#define SMALL 5
#define LARGE 200
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, Q;
char A[SMALL][LARGE];
char M[LARGE];
int S[LARGE];

int check(char* a, char* b, int bg, int ed, int sc) {
  int cnt = 0, tl = ed + 1 - bg;
  inc (i, bg, ed + 1) if (a[i] == b[i]) ++cnt;
  if (sc <= cnt) return tl - cnt + sc;
  return tl - sc + cnt;
}

void exchange(char* s, int l, int r) {
  char m = s[l];
  s[l] = s[r];
  s[r] = m;
}

int depart() {
  int cnt = 1;
  inc (i, 1, Q + 1) {
    if (A[1][i] == A[2][i]) {
      exchange(A[1], cnt, i);
      exchange(A[2], cnt, i);
      exchange(M, cnt, i);
      ++cnt;
    }
  }
  return cnt;
}

int solve() {
  if (N == 1) return check(A[1], M, 1, Q, S[1]);
  int m = depart();
  // cmp s1 s2
  int s1 = ((S[1] + S[2]) - (Q - m + 1)) >> 1;
  int s2 = ((Q - m + 1) - (S[2] - S[1])) >> 1;
  return check(A[1], M, 1, m - 1, s1) + check(A[1], M, m, Q, s2);
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
    scanf("%d %d", &N, &Q);
    inc (i, 1, N + 1) scanf("%s", A[i] + 1);
    scanf("%s", M + 1);
    inc (i, 1, N + 1) scanf("%d", &S[i]);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

