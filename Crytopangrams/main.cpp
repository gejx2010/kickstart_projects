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
#define PRV(x) cout << #x << ": "; for (auto& x##_it: x) cout << x##_it << ' '; cout << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 205
#define PLARGE 100000
#define COM 26
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, L;
ll A[LARGE];
ll B[LARGE];
char S[LARGE];
ll pcnt;
ll P[PLARGE];
ll V[PLARGE];
set<ll> srt;
map<ll, ll> srm;

void precmp() {
  pcnt = 0;
  memset(V, 0, sizeof V);
  V[1] = 1;
  ll bg = 2;
  while ((bg << 1) < PLARGE) {
    P[++pcnt] = bg;
    ll c = bg << 1;
    while (c < PLARGE) { V[c] = 1; c += bg; }
    ++bg;
    while (V[bg]) ++bg;
  }
  //PR(pcnt);
  //PRA(P, pcnt + 1);
}

void cmp(ll x, ll& a, ll& b) {
  inc (i, 1, pcnt + 1) {
    if (x % P[i] == 0) {
      a = P[i];
      b = x / P[i];
      break;
    }
  }
}

bool decrypt(ll rk, ll v) {
  //PR(rk);
  //PR(v);
  //PR(A[rk]);
  B[rk] = v;
  if (rk == L + 1) return true;
  if (A[rk] % v != 0) return false;
  return decrypt(rk + 1, A[rk] / v);
}

void decode() {
  srt.clear();
  srm.clear();
  inc (i, 1, L + 2) {
    if (srt.size() == COM) break;
    srt.insert(B[i]);
  }
  //PRV(srt);
  //PRV(srt);
  int cnt = 0;
  for (auto n: srt) srm[n] = ++cnt;

  inc (i, 1, L + 2) 
    S[i] = 'A' + srm[B[i]] - 1;
  S[L + 2] = '\0';
}

void solve() {
  //ll fm = LLONG_MAX, fmr = 0;
  //inc (i, 1, L + 1) {
  //  if (A[i] < fm) {
  //    fm = A[i];
  //    fmr = i;
  //  }
  //}
  //PR(fm);
  //PR(fmr);
  ll a, b;
  cmp(A[1], a, b);
  if (!decrypt(1, a)) decrypt(1, b);

  decode();
  //PR(a);
  //PR(b);
  //if (1 < fmr) {
  //  if (A[fmr - 1] % a == 0) {
  //    decrypt(fmr, a);
  //  } else {
  //    decrypt(fmr, b);
  //  }
  //} else {
  //  if (A[fmr + 1] % a == 0) {
  //    decrypt(fmr, b);
  //  } else {
  //    decrypt(fmr, a);
  //  }
  //}
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  precmp();
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    scanf("%lld %lld", &N, &L);
    inc (j, 1, L + 1) 
      scanf("%lld", &A[j]);
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %s\n", i, S + 1);
  }
  return 0;
}

