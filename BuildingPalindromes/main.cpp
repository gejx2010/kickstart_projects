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
#define PRA(x,sz) cerr << #x << ": " << endl; for (int xit = 0; xit < (sz); ++(xit)) cerr << (x)[xit] << " "; cerr << endl;
#define PRV(x) cout << #x << ": "; for (auto& xit: x) cout << xit << ' '; cout << endl;
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
#define COM 26
#define COMPILE false
#define TESTTIME false
#define MOD 1000000007
#define num(x) ((x) - 'A')

// define initial parameters here
int T = 0;
int N, Q;
string S;
int L[LARGE], R[LARGE];
vi sum[LARGE];

bool pad(int l, int r) {
  int ne = 0;
  inc (i, 0, COM) {
    if (sum[r][i] == sum[l][i]) continue;
    else ++ne;
    if (1 < ne) return false;
  }
  return true;
}

int solve() {
  vi v;
  inc (i, 0, COM + 1) v.pb(0);
  sum[0] = v;
  inc (i, 1, N + 1) {
    sum[i] = sum[i - 1];
    if (sum[i][num(S[i - 1])] == 0) sum[i][num(S[i - 1])] = 1;
    else sum[i][num(S[i - 1])] = 0;
    //PR(i);
    //PRV(sum[i]);
  }
  int res = 0;
  inc (i, 1, Q + 1) {
    res += pad(L[i] - 1, R[i]) ? 1 : 0;
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
    cin >> N >> Q;
    cin >> S;
    inc (j, 1, Q + 1) cin >> L[j] >> R[j];
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

