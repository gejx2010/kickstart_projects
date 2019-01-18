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
#define PRA(x,sz) cout << #x << ": " << endl; for (int x##_it = 0; x##_it <= (sz); ++(x##_it)) cout << (x)[x##_it] << " "; cout << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)
#define lson(x) (((x) << 1) + 1)
#define rson(x) (((x) << 1) + 2)

#define LARGE 16
#define MLARGE 3010
#define LLARGE 1000000
#define ARRAY_SIZE (1 << 13)
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0, N;
int A[LARGE], B[LARGE];
tpi sma[LLARGE];
tpi smb[LLARGE];
int smas; // size of sma
int smbs; // size of smb
int aless[MLARGE];
int bless[MLARGE];
int aosz; // size of aless
int bosz; // size of bless
int column[MLARGE];
int tcolumn[MLARGE];
int rmin;
multiset<int> map_col[MLARGE];
int dless[MLARGE][MLARGE];
int tless[MLARGE][MLARGE];
int combo[LARGE][LARGE];
int AA[4], BB[4];
int sum_a, sum_b;
int ss[LARGE], mm[LARGE], om[LARGE];
int sum_ss, sum_mm;
bool first_end, sec_end;
int mark[LARGE];
int stree[ARRAY_SIZE][ARRAY_SIZE];
map<int, int> rma, rmb;
pri check_id[ARRAY_SIZE];
int upm, upr;

void precompute() {
  for (int i = 1; i < LARGE; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == 0) combo[i][j] = 1;
      else if ((i >> 1) < j) combo[i][j] = combo[i][i - j];
      else combo[i][j] = combo[i - 1][j - 1] + combo[i - 1][j];
    }
  }
}

int select(int beg, int an, int sn) {
  if (an == 0) return 0;
  int bias = sn;
  int res = 0;
  for (int i = beg; i <= 3 * N - an + 1; ++i) {
    int v = A[i];
    if (sn < v) break;
    int sv = select(i + 1, an - 1, sn - v);
    if (v + sv < sn) {
      int cb = sn - (v + sv);
      if (cb < bias) {
        bias = cb;
        res = v + sv;
      }
    } else if (v + sv == sn) return sn;
  }
  return res;
}

void depart() {
  sort(A + 1, A + 3 * N + 1);
  sum_a = 0;
  for (int i = 1; i <= 3 * N; ++i) {
    sum_a += A[i];
    if (i == N) AA[1] = sum_a;
  }
  int leave = sum_a - AA[1];
  int beg = N + 1;
  AA[2] = select(beg, N, leave >> 1);
  AA[3] = leave - AA[2];
}

int is_valid() {
  int cnt = 0;
  for (int i = 1; i <= 3; ++i)
    if (BB[i] < AA[i]) ++cnt;
  if (1 < cnt) return 1;
  return 0;
}

void sel_first(int* arr) {
  sum_ss = 0;
  memset(mark, 0, sizeof mark);
  for (int i = 1; i <= N; ++i) {
    ss[i] = i;
    sum_ss += arr[i];
    mark[i] = 1;
  }
  ss[N + 1] = 3 * N + 1;
  first_end = false;
}

void sel_first_sec(int* arr) {
  sum_mm = 0;
  int rk = 1; 
  for (int i = 1; i <= 3 * N && rk <= N; ++i) {
    if (!mark[i]) {
      mm[rk] = i;
      om[rk] = i;
      ++rk;
      sum_mm += arr[i];
    }
  }
  mm[N + 1] = 3 * N + 1;
  om[N + 1] = 3 * N + 1;
  sec_end = false;
}

void next_iter(int* arr) {
  int rk = 1;
  for (int i = ss[1] + 1; i <= 3 * N; ++i) {
    if (mark[i]) ++rk;
    else {
      mark[ss[rk]] = 0;
      ss[rk] = i;
      mark[i] = 1;
      for (int j = 1; j < rk; ++j) { 
        mark[ss[j]] = 0;
        ss[j] = j; 
        mark[j] = 1; 
      }
      sum_ss = 0;
      for (int j = 1; j <= N; ++j) sum_ss += arr[ss[j]];
      first_end = false;
      return;
    }
  }
  first_end = true;
}

void next_iter_sec(int* arr) {
  int rk = 1;
  for (int i = mm[1] + 1; i <= 3 * N; ++i) {
    if (i == mm[rk + 1]) ++rk;
    else if (!mark[i]) {
      mm[rk] = i;
      for (int j = 1; j < rk; ++j) mm[j] = om[j];
      sum_mm = 0;
      for (int j = 1; j <= N; ++j) sum_mm += arr[mm[j]];
      sec_end = false;
      return;
    }
  }
  sec_end = true;
}

void visit(int* arr, int& sum, int* ls, int& osz, tpi* m, int& sz) {
  sum = accumulate(arr + 1, arr + 3 * N + 1, 0);
  sz = 0;
  set<int> lsm;
  for (sel_first(arr); !first_end; next_iter(arr)) {
    if (!lsm.count(sum_ss)) lsm.insert(sum_ss);
    for (sel_first_sec(arr); !sec_end; next_iter_sec(arr)) 
      m[sz++] = mt(sum_ss, sum_mm, sum - sum_ss - sum_mm);
  }
  osz = 0;
  for (auto& it: lsm) ls[osz++] = it;
  ls[osz] = INT_MAX;
  sort(m, m + sz);
}

void compute_less() {
  // compute P(x, y)
  clock_t st = clock();
  memset(dless, 0, sizeof dless);
  memset(tless, 0, sizeof tless);
  memset(column, 0, sizeof column);
  int rk = 0;
  for (int i = 0; i < aosz; ++i) {
    int upb = aless[i];
    // add column
    int l, m, r;
    tie(l, m, r) = smb[rk];
    while (l < upb && rk < smbs) {
      int cl = l;
      for (int j = 0; j <= aosz && rk < smbs; ++j) {
        int rtb = aless[j];
        int ktb = sum_a - upb - rtb;
        while (l == cl && m < rtb && rk < smbs) {
          ++column[j];
          tie(l, m, r) = smb[++rk];
        }
        if (upb <= l || smbs <= rk) break;
        if (cl < l) { 
          j = -1; 
          cl = l; 
        }
      }
    }
    // add to dless[i][j] & tless[i][j]
    int sum = 0;
    for (int j = 0; j < aosz; ++j) {
      // compute dless[i][j]
      sum += column[j];
      dless[i][j] = sum;
    }
  }
  debug("process dless takeds time: %f seconds.\n", ((float)clock() - st) / CLOCKS_PER_SEC);
}

void update_layer_y(int xid, int yid) {
  int yb = check_id[yid].first, ye = check_id[yid].second;
  if (upr < yb || ye <= upr) return;
  ++stree[xid][yid];
  if (ye - yb <= 1) return;
  int mid = (yb + ye) >> 1;
  if (upr < mid) update_layer_y(xid, lson(yid));
  else update_layer_y(xid, rson(yid));
}

void update_layer(int xid) {
  int xb = check_id[xid].first, xe = check_id[xid].second;
  if (upm < xb || xe <= upm) return;
  update_layer_y(xid, 0);
  if (xe - xb <= 1) return;
  int mid = (xb + xe) >> 1;
  if (upm < mid) update_layer(lson(xid));
  else update_layer(rson(xid));
}

void update_tree(int rk) {
  int l, m, r;
  tie(l, m, r) = smb[rk];
  upm = rmb[m], upr = rmb[r];
  update_layer(0);
}

int search_layer_y(int xid, int yid) {
  int yb = check_id[yid].first, ye = check_id[yid].second;
  int l = bless[yb], h = bless[ye - 1];
  if (upr <= l) return 0;
  if (h < upr) return stree[xid][yid];
  int mid = (yb + ye) >> 1;
  int sum = 0;
  sum += search_layer_y(xid, lson(yid));
  sum += search_layer_y(xid, rson(yid));
  return sum;
}

int search_layer(int xid) {
  int xb = check_id[xid].first, xe = check_id[xid].second;
  int l = bless[xb], h = bless[xe - 1];
  if (upm <= l) return 0;
  if (h < upm) return search_layer_y(xid, 0);
  int mid = (xb + xe) >> 1;
  int sum = 0;
  sum += search_layer(lson(xid));
  sum += search_layer(rson(xid));
  return sum;
}

int search_tree(int m, int r, int mm, int rr) {
  upm = m, upr = r;
  if (0 <= tless[mm][rr]) return tless[mm][rr];
  return (tless[mm][rr] = search_layer(0));
}

void build_id_each(int id, int st, int ed) {
  check_id[id] = mp(st, ed);
  if (ed - st == 1) return;
  int mid = (st + ed) >> 1;
  build_id_each(lson(id), st, mid);
  build_id_each(rson(id), mid, ed);
}

void build_id() {
  build_id_each(0, 0, bosz);
}

int count() {
  for (int i = 0; i < aosz; ++i) rma[aless[i]] = i;
  for (int i = 0; i < bosz; ++i) rmb[bless[i]] = i;
  int cnt = 0;
  memset(stree, 0, sizeof stree);
  memset(tless, -1, sizeof tless);
  build_id();
  int rk = 0;
  for (int i = 0; i < smas; ++i) {
    int l = 0, m = 0, r = 0;
    tie(l, m, r) = sma[i];
    auto it = lower_bound(smb + rk, smb + smbs, mt(l, 0, 0));
    int nrk = it - smb;
    for (int j = rk; j < nrk; ++j) { 
      update_tree(j);
    }
    rk = nrk;
    int ll = rma[l], mm = rma[m], rr = rma[r];
    int s1 = dless[ll][mm];
    int s2 = dless[ll][rr];
    int s3 = dless[mm][rr];
    int s4 = search_tree(m, r, mm, rr);
    int cc = s1 + s2 + s3 - (s4 << 1);
    if (cnt < cc) {
      cnt = cc;
    }
  }
  return cnt;
}

double solve() {
  clock_t st = clock();
  // visit B to get <first, second> pair array for B
  visit(B, sum_b, bless, bosz, smb, smbs);
  // visit A to get <first, second> pair array for A
  visit(A, sum_a, aless, aosz, sma, smas);
  debug("visit array takeds time: %f seconds.\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  // compute P(x1, x2)
  st = clock();
  compute_less();
  // iterate on A to get the max count
  int cnt = count();
  debug("count takeds time: %f seconds.\n", ((float)clock() - st) / CLOCKS_PER_SEC);
  ll all = combo[3 * N][N] * combo[2 * N][N];
  return (double)cnt / all;
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  // precompute combo
  precompute();
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    scanf("%d", &N);
    for (int j = 1; j <= 3 * N; ++j) scanf("%d", &A[j]);
    for (int j = 1; j <= 3 * N; ++j) scanf("%d", &B[j]);
    double res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.9f\n", i, res);
  }
  return 0;
}

