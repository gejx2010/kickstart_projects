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
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 200001
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, K, A1, B1, C, D, E1, E2, F;
ll x, y, xx, yy, r, s, rr, ss;
ll A[LARGE], B[LARGE];
ll SA[LARGE], SB[LARGE];
ll LSA[LARGE], LSB[LARGE];
ll ASZ, BSZ;

void cmp_sum(ll* a, ll* s) {
  s[0] = 0;
  rep(i,1,N+1) s[i] = s[i - 1] + a[i];
}

int cmp_lsum(ll* a, ll* s) {
  int rk = 0;
  rep(i,1,N+1) {
    ll sum = 0;
    rep(j,i,N+1) {
      sum += a[j];
      s[++rk] = sum;
    }
  }
  sort(s + 1, s + rk + 1);
  return rk;
}

ll find_kth(ll m) {
  auto git = upper_bound(LSA + 1, LSA + ASZ + 1, 0);
  auto lit = lower_bound(LSA + 1, LSA + ASZ + 1, 0);
  int grk = git - LSA;
  int lrk = lit - LSA;
  // count greater than 0
  ll res = 0;
  rep(i,1,lrk) {
    //PR(m);
    //PR(LSA[i]);
    ll v = m / LSA[i];
    //PR(v);
    auto mit = LSB;
    if (0 <= m) mit = lower_bound(LSB + 1, LSB + BSZ + 1, v);
    else if (v * LSA[i] == m) mit = lower_bound(LSB + 1, LSB + BSZ + 1, v);
    else mit = upper_bound(LSB + 1, LSB + BSZ + 1, v);
    //PR(*mit);
    //PR(*(mit-1));
    //PR(mit - LSB);
    res += (mit - LSB) - 1;
  }
  rep(i,grk,ASZ+1) {
    auto mit = LSB;
    ll v = m / LSA[i];
    if (0 <= m) mit = upper_bound(LSB + 1, LSB + BSZ + 1, v);
    else if (v * LSA[i] == m) mit = upper_bound(LSB + 1, LSB + BSZ + 1, v);
    else mit = lower_bound(LSB + 1, LSB + BSZ + 1, v);
    res += BSZ + 1 - (mit - LSB);
  }
  return res + 1;
}

ll solve() {
  // cmp sum
  ASZ = cmp_lsum(A, LSA);
  BSZ = cmp_lsum(B, LSB);

  // bin search k
  ll u = max(LSA[ASZ] * LSB[BSZ], LSA[1] * LSB[1]);
  ll d = min(LSA[1] * LSB[BSZ], LSA[ASZ] * LSB[1]);
  PR(u);
  PR(d);
  PR(ASZ);
  PR(K);
  while (d <= u) {
    ll m = (u + d) >> 1;
    if (find_kth(m) <= K) u = m - 1;
    else d = m + 1;
  }
  PR(u+1);
  return u + 1;
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
    cin >> N >> K >> A1 >> B1 >> C >> D >> E1 >> E2 >> F;
    A[1] = A1, B[1] = B1;
    xx = A[1], yy = B[1], rr = 0, ss = 0;
    rep(j,2,N+1) {
      x = (C * xx + D * yy + E1) % F;
      y = (D * xx + C * yy + E2) % F;
      xx = x, yy = y;
      r = ((C * rr + D * ss + E1) & 1);
      s = ((D * rr + C * ss + E2) & 1);
      rr = r, ss = s;
      A[j] = (r & 1) ? -x : x;
      B[j] = (s & 1) ? -y : y;
    }
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

