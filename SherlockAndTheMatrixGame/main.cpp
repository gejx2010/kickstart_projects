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

#define PR(x) cout << #x << ": " << (x) << endl;
#define PRA(x,sz) cout << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cout << (x)[x##_it] << " "; cout << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)
#define lch(r) ((r) << 1)
#define rch(r) (((r) << 1) + 1)

#define LARGE 200001
#define MIDDLE 20
#define OLARGE 100000007L
#define OOLARGE OLARGE * OLARGE
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
ll N, K, A1, B1, C, D, E1, E2, F, M;
ll x, y, xx, yy, r, s, rr, ss;
ll A[LARGE], B[LARGE];
prl SA[LARGE];
prl SSA[LARGE];
map<prl, ll> HMA;
tpl TS[MIDDLE][LARGE];
bool TURN;
ll GSA[LARGE], GSB[LARGE];
ll GSAZ, GSBZ;
ll MSA[LARGE], MSB[LARGE];
ll MSAZ, MSBZ;
ll UPA[LARGE << 1], UPB[LARGE << 1];
ll UPAZ, UPBZ;

ll LSA[LARGE], LSB[LARGE];
ll ASZ, BSZ;

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
    ll v = m / LSA[i];
    auto mit = LSB;
    if (0 <= m) mit = lower_bound(LSB + 1, LSB + BSZ + 1, v);
    else if (v * LSA[i] == m) mit = lower_bound(LSB + 1, LSB + BSZ + 1, v);
    else mit = upper_bound(LSB + 1, LSB + BSZ + 1, v);
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
  //PR(u);
  //PR(d);
  //PR(ASZ);
  //PR(K);
  while (d <= u) {
    ll m = (u + d) >> 1;
    if (find_kth(m) <= K) u = m - 1;
    else d = m + 1;
  }
  //PR(u+1);
  return u + 1;
}

void cmp_sum(ll* a) {
  HMA.clear();
  // compute layer 1
  SSA[0] = SA[0] = {0, 0};
  rep(i,1,N+1) SSA[i] = SA[i] = {SA[i - 1].first + a[i], i}; 
  sort(SSA + 1, SSA + N + 1);
  inc(i,0,N+1) HMA[SSA[i]] = i;
}

void insert_tree(prl v, ll cnt) {
  ll rk = HMA[v];
  TS[0][rk] = (cnt == 0) ? mt(0LL, 0LL, 0LL) : mt(v.first, v.first, cnt);
  ll ly = 0, c = rk;
  while (ly < MIDDLE - 1) {
    c >>= 1;
    ll aa, ab, ac, ba, bb, bc;
    tie(aa, ab, ac) = TS[ly][lch(c)];
    tie(ba, bb, bc) = TS[ly][rch(c)];
    if (bc == 0) TS[ly + 1][c] = mt(aa, ab, ac);
    else if (ac == 0) TS[ly + 1][c] = mt(ba, bb, bc);
    else TS[ly + 1][c] = mt(aa, bb, ac + bc);
    ++ly;
  }
  //debug("now TS[%lld][%lld]: (%lld, %lld %lld)\n", ly, c, gel(TS[ly][c], 0), gel(TS[ly][c], 1), gel(TS[ly][c], 2));
}

ll search_ltree(ll ly, ll id, ll n) {
  //debug("begin with ly: %lld, id: %lld, number: %lld\n", ly, id, n);
  ll a, b, c;
  tie(a, b, c) = TS[ly][id];
  //debug("tie(%lld, %lld, %lld)\n", a, b, c);
  if (c == 0) return 0;
  if (b <= n) return 0;
  if (n < a) return c;
  ll lc = lch(id), rc = rch(id);
  return search_ltree(ly - 1, lc, n) + search_ltree(ly - 1, rc, n);
}

ll search_mtree(ll ly, ll id, ll n) {
  ll a, b, c;
  tie(a, b, c) = TS[ly][id];
  if (c == 0) return 0;
  if (b < n) return c;
  if (n <= a) return 0;
  ll lc = lch(id), rc = rch(id);
  return search_mtree(ly - 1, lc, n) + search_mtree(ly - 1, rc, n);
}

ll find_lrk(ll k) {
  clock_t st = clock();
  //debug("find_lrk with n: %lld\n", k);
  ll rk = 0;
  if (TURN) {
    dec(i, N, 0) {
      clock_t bf = clock();
      //debug("inside dec, rk now is: %lld\n", i);
      ll n = search_ltree(MIDDLE - 1, 0, SA[i].first + k);
      clock_t md = clock();
      //debug("search_ltree takes time: %f\n", ((float)md - bf) / CLOCKS_PER_SEC);
      //debug("end with res: %lld\n", n);
      rk += n;
      insert_tree(SA[i], 1);
      clock_t ed = clock();
      //debug("insert_tree takes time: %f\n", ((float)ed - md) / CLOCKS_PER_SEC);
    }
  } else {
    inc(i, 0, N + 1) {
      clock_t md = clock();
      //debug("inside inc, rk now is: %lld\n", i);
      insert_tree(SA[i], 0);
      clock_t ed = clock();
      //debug("delete_tree takes time: %f\n", ((float)ed - md) / CLOCKS_PER_SEC);
      ll n = search_ltree(MIDDLE - 1, 0, SA[i].first + k);
      clock_t bf = clock();
      //debug("search_ltree takes time: %f\n", ((float)bf - ed) / CLOCKS_PER_SEC);
      //debug("end with res: %lld\n", n);
      rk += n;
    }
  }
  TURN = !TURN;
  //debug("find_lrk with rank: %lld\n", rk + 1);
  //debug("find_lrk takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  return rk + 1;
}

ll find_mrk(ll k) {
  //debug("find_mrk with number: %lld\n", k);
  ll rk = 0;
  if (TURN) {
    dec(i, N, 0) {
      rk += search_mtree(MIDDLE - 1, 0, SA[i].first + k);
      insert_tree(SA[i], 1);
    }
  } else {
    inc(i, 0, N + 1) {
      insert_tree(SA[i], 0);
      rk += search_mtree(MIDDLE - 1, 0, SA[i].first + k);
    }
  }
  TURN = !TURN;
  //debug("find_mrk return result: %lld\n", rk + 1);
  return rk + 1;
}

void get_lrk(ll* ss, ll& sz, ll k) {
  multimap<ll, ll> m;
  sz = 0;
  dec(i, N, 0) {
    auto it = m.upper_bound(SA[i].first + k);
    while (it != m.end()) {
      ll v = (*it).first, id = (*it).second;
      ss[++sz] = v - SA[i].first;
      ++it;
    }
    m.insert(SA[i]);
  }
  while (sz < min(K, M)) ss[++sz] = k;
  sort(ss + 1, ss + sz + 1);
}

void get_mrk(ll* ss, ll& sz, ll k) {
  multimap<ll, ll> m;
  sz = 0;
  dec(i, N, 0) {
    auto it = m.lower_bound(SA[i].first + k);
    while (it != m.begin()) {
      --it;
      ll v = (*it).first, id = (*it).second;
      ss[++sz] = v - SA[i].first;
    }
    m.insert(SA[i]);
  }
  while (sz < min(K, M)) ss[++sz] = k;
  sort(ss + 1, ss + sz + 1);
}

void get_largest(ll* ss, ll& sz) {
  clock_t st = clock();
  ll u = OLARGE, d = - OLARGE, m = 0;
  memset(TS, 0, sizeof TS);
  //debug("within get_largest, memset takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  st = clock();
  TURN = true;
  while (d <= u) {
    clock_t est = clock();
    m = (u + d) >> 1;
    if (find_lrk(m) <= min(K, M)) u = m - 1;
    else d = m + 1;
    //debug("within get_largest, find rank(%lld) takes time: %f\n", m, ((float)clock() - est) / CLOCKS_PER_SEC);
  }
  //debug("within get_largest, find the Kth num takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  //debug("get_largest, return res: %lld\n", u + 1);
  st = clock();
  get_lrk(ss, sz, u + 1);
  //debug("within get_largest, merge the largest takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
}

void get_smallest(ll* ss, ll& sz) {
  clock_t st = clock();
  ll u = OLARGE, d = - OLARGE, m = 0;
  memset(TS, 0, sizeof TS);
  //debug("within get_smallest, memset takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  TURN = true;
  st = clock();
  while (d <= u) {
    clock_t est = clock();
    m = (u + d) >> 1;
    if (find_mrk(m) <= min(K, M)) d = m + 1;
    else u = m - 1;
    //debug("within get_smallest, find rank(%lld) takes time: %f\n", m, ((float)clock() - est) / CLOCKS_PER_SEC);
  }
  //debug("within get_smallest, find the Kth num takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  st = clock();
  get_mrk(ss, sz, d - 1);
  //debug("within get_smallest, merge the smallest takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
}

void merge_lm(ll* a, ll asz, ll* b, ll bsz, ll* c, ll& csz) {
  ll ck = min(M - K, K);
  csz = 0;
  rep (i, 1, ck + 1) c[++csz] = b[i];
  rep (i, 1, asz + 1) c[++csz] = a[i];
}

ll find_frk(ll v) {
  auto it = UPB;
  ll rk = 0;
  dec(i, UPAZ, 1) {
    if (0 <= v) {
      if (0 < UPA[i]) {
        it = upper_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        rk += UPBZ - (it - UPB) + 1;
      } else if (UPA[i] == 0) {
        rk += 0;
      } else {
        it = lower_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        rk += (it - UPB) - 1;
      }
    } else {
      if (0 < UPA[i]) {
        if (v % UPA[i] == 0) it = upper_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        else it = lower_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        rk += UPBZ + 1 - (it - UPB);
      } else if (UPA[i] == 0) {
        rk += UPBZ;
      } else {
        if (v % UPA[i] == 0) it = lower_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        else it = upper_bound(UPB + 1, UPB + UPBZ + 1, v / UPA[i]);
        rk += (it - UPB) - 1;
      }
    }
  }
  return rk + 1;
}

ll search() {
  ll u = OOLARGE, d = - OOLARGE, m = 0;
  while (d <= u) {
    m = (u + d) >> 1;
    //debug("final search, current (u, d, m): (%lld, %lld, %lld)\n", u, d, m);
    if (find_frk(m) <= K) u = m - 1;
    else d = m + 1;
    //debug("final search, current (u, d, m): (%lld, %lld, %lld)\n", u, d, m);
  }
  return u + 1;
}

ll solve_large() {
  if (N == 1) return A[1] * B[1];
  
  clock_t st = clock();
  // get A down
  cmp_sum(A);
  get_largest(GSA, GSAZ);
 
  debug("get largest A takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);

  st = clock();
  //PR(GSAZ);
  //rep(i,1,GSAZ+1) debug("GSA[%lld]: (%lld, %lld, %lld)\n", i, gel(GSA[i], 0), gel(GSA[i], 1), gel(GSA[i], 2));
  get_smallest(MSA, MSAZ);
  //rep(i,1,MSAZ+1) debug("MSA[%lld]: (%lld, %lld, %lld)\n", i, gel(MSA[i], 0), gel(MSA[i], 1), gel(MSA[i], 2));
  debug("get smallest A takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);

  st = clock();
  cmp_sum(B);
  get_largest(GSB, GSBZ);
  debug("get largest B takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);

  st = clock();
  //PR(GSBZ);
  //rep(i,1,GSBZ+1) debug("GSB[%lld]: (%lld, %lld, %lld)\n", i, gel(GSB[i], 0), gel(GSB[i], 1), gel(GSB[i], 2));
  get_smallest(MSB, MSBZ);
  debug("get smallest B takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  //rep(i,1,MSBZ+1) debug("MSB[%lld]: (%lld, %lld, %lld)\n", i, gel(MSB[i], 0), gel(MSB[i], 1), gel(MSB[i], 2));


  st = clock();
  // merge array
  merge_lm(GSA, GSAZ, MSA, MSAZ, UPA, UPAZ);
  merge_lm(GSB, GSBZ, MSB, MSBZ, UPB, UPBZ);

  debug("merge array takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  //PRA(UPA, UPAZ + 1);
  //PRA(UPB, UPBZ + 1);

  // compute Kth largest
  st = clock();
  ll res = search();
  debug("search final result takes time: %f\n", ((float)clock() - st) / CLOCKS_PER_SEC);
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
    cin >> N >> K >> A1 >> B1 >> C >> D >> E1 >> E2 >> F;
    M = ((N + 1) * N) >> 1;
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
    ll res = solve_large();
    //PRA(LSUM, LSSZ + 1);
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %lld\n", i, res);
  }
  return 0;
}

