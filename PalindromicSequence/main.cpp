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
#include <climits>
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

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)
#define chr(i) ('a' + (i))

#define LARGE 1e12
#define COMPILE false
#define TESTTIME true
#define COM 27
#define LCOM 100

// define initial parameters here
int T = 0;
ll L, N, K;
ll S[COM][LCOM];
int MS[COM];

void precompute() {
  memset(S, 0, sizeof S);
  memset(MS, 0, sizeof MS);
  // i for L
  for (int i = 2; i < COM; ++i) {
    int j = 1;
    ll add = 1;
    ll sum = 0;
    while (sum <= LARGE) {
      if ((j & 1) == 1) add *= i;
      sum += add;
      S[i][j] = sum;
      ++j;
    }
    MS[i] = j;
  }
}

bool pld(const char* s, int len) {
  if (len <= 1) return true;
  int i = -1;
  int j = len;
  while (i < j) if (s[++i] != s[--j]) return false;
  return true;
}

// to see with pref's a
bool ppld(const char* s, int len, ll pref) {
  if (len < 1) return true;
  if (pref < 1) return pld(s, len);
  int l = 1;
  int r = len - 1;
  while (l <= pref && 0 <= r) {
    if (s[r] != chr(0)) return false;
    --r, ++l;
  }
  if (l <= pref) return true;
  l = 0; 
  while (l < r) if (s[l++] != s[r--]) return false;
  return true;
}

// calculate rank with pref's a + s
ll cnt_rank(string s, ll pref) {
  ll cnt = 0;
  ll len = s.length();
  // cnt pld(s)
  int i = 0;
  for (; i <= len; ++i) {
    if (N < len + i + (pref << 1)) break;
    cnt += pld(s.c_str() + i, len - i);
  }
  //PR("cnt self");
  //PR(cnt);
  // cnt pld for s - pref
  string ns(s);
  i = 1;
  for (; i <= min(len, pref); ++i) {
    ns = 'a' + ns;
    if (len + (pref << 1) - i <= N) cnt += pld(ns.c_str(), len + i);
  }
  if (len < pref) {
    ll ad = min(pref - len, N - pref - len);
    cnt += ad * pld(ns.c_str(), len << 1);
  }
  //PR("cnt pref");
  //PR(cnt);
  ll lv = N - ((pref + len) << 1);
  if (MS[L] <= lv) cnt += LARGE;
  else if (1 <= lv) cnt += S[L][lv];
  //PR("cnt S");
  //PR(cnt);
  return cnt;
}

int max_pal_len(string s) {
  for (int i = s.length(); 0 <= i; --i) 
    if (pld(s.c_str(), i)) return i;
  return 0;
}

ll solve() {
  if (L == 1) {
    if (N < K) return 0;
    else return K;
  }
  // find the first p that S[L][p] > K
  int p = 0;
  for (int i = 1; i <= MS[L]; ++i) {
    if (K <= S[L][i]) {
      p = i;
      break;
    }
  }
  //PR(L);
  //PR(N);
  //PR(K);
  //PR(p);
  //PR(S[L][p]);
  if (N < p) return 0;
  // calculate prefix a's length
  ll pref = 0;
  if (p + 1 < N) pref = (N - p) >> 1;
  if (K <= pref) return K;
  K -= pref;
  //PR(pref);
  // do with the leave
  string s = "";
  while (0 < K) {
    for (int i = 0; i < L; ++i) {
      string ns(s);
      ns += chr(i);
      ll r = cnt_rank(ns, pref); 
      //PR(ns);
      //PR(r);
      //PR(K);
      if (K <= r) { 
       s = ns;
       if (N <= (pref << 1) + s.length()) {
         if (1 < r) {
           return pref + s.length() + K - 1;
         } else {
           int mv = max_pal_len(s);
           return (pref << 1) + mv;
         }
       } else if (ppld(s.c_str(), s.length(), pref)) --K;
       break; 
      } else 
        K -= r; 
    }
  }
  return pref + s.length();
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
  precompute();
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    scanf("%lld %lld %lld", &L, &N, &K);
    ll res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

