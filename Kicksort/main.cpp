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

#define LARGE 20001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T, N;
int A[LARGE];

struct BIT {
  int a[LARGE];

  BIT() { memset(a, 0, sizeof a); }
  
  void clear() { memset(a, 0, sizeof a); }

  void add(int num, int times) {
    if (num == 0) { a[0] += times; return; }
    for (int i = num; i < LARGE; i += (i & -i)) 
      a[i] += times;
  }

  int query(int num) {
    int res = 0;
    for (int i = num; 0 < i; i -= (i & -i))
      res += a[i];
    return res + a[0];
  }
} bit;

int findk(int k) {
  //PR("begin findk");
  //PR(k);
  int l = 0, r = N - 1, med; 
  while (l <= r) {
    med = (l + r) >> 1;
    int kth = med - bit.query(med);
    //PR(l);
    //PR(r);
    //PR(k);
    //PR(med);
    //PR(kth);
    if (k <= kth) r = med - 1;
    else l = med + 1;
  }
  //PR("end findk");
  return r + 1;
}

string solve() {
  if (N == 2) return "YES";
  bit.clear();
  int n = N;
  int low = 1, high = N;
  while (low < high) {
    int med = findk((n - 1) >> 1);
    //PR(low);
    //PR(high);
    //PR(med);
    //PR(A[med]);
    if ((A[med] != low) && (A[med] != high)) return "NO";
    if (A[med] == low) ++low;
    else if (A[med] == high) --high;
    bit.add(med, 1);
    --n;
  }
  return "YES";
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
    rep (j,0,N) scanf("%d", &A[j]);
    string res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %s\n", i, res.c_str());
  }
  return 0;
}

