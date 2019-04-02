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
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cout << #x << ": "; for (auto& x##_it: x) cout << x##_it << ' '; cout << endl;
#define debug(...) fprintf(stdout, __VA_ARGS__)
#define rep(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define inc(i,a,b) for (decltype(b) i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define dec(i,a,b) for (decltype(a) i = (a), i##_end_ = (b); i##_end_ <= i; --i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define gel(x,i) get<(i)>(x)

#define LARGE 1000007
#define MIDDLE 25
#define COMPILE false
#define TESTTIME true
#define lch(x) ((x) << 1)
#define rch(x) (((x) << 1) + 1)
#define ltp(x) ((x).first <= 0) ? mp((x).first - 1, lch((x).second)) : mp((x).first + 1, lch((x).second))
#define rtp(x) ((x).first < 0) ? mp((x).first - 1, rch((x).second)) : mp((x).first + 1, rch((x).second))
#define fth(x) ((x).first < 0) ? mp((x).first + 1, (x).second >> 1) : mp((x).first - 1, (x).second >> 1)

// define initial parameters here
int T = 0;
int N, Q;
int L[LARGE], R[LARGE];
int LL[LARGE], RR[LARGE], W[LARGE];
pri QP[LARGE];
tpi QU[LARGE];
int TS[MIDDLE][LARGE];
map<int, set<pri>> hm;
set<pri> sp[LARGE];
int spz;

using ivtp = tuple<set<pri>, vpri, vpri, si, int>;
using svtp = tuple<pri, int, int, int>;

// using rb tree to setup interval tree
map<pri, ivtp> TM;
map<pri, svtp> TMS;
si insi;
vpri invi;

int insert(int lx, int ly, int lv, int rv, int a, int b, bool write) {
  debug("insert lx, ly, lv, rv, a, b: (%d, %d, %d, %d, %d, %d)\n", lx, ly, lv, rv, a, b);
  if (b < a || rv < lv) return 0;
  if (b < lv || rv < a) return 0;
  if (TS[lx][ly] == rv - lv + 1) return 0;
  if (a == lv && rv == b) {
    int m = TS[lx][ly];
    if (write) TS[lx][ly] = b - a + 1; 
    return b - a + 1 - m;
  }
  int m = (lv + rv) >> 1;
  if (b <= m) {
    int nn = insert(lx + 1, lch(ly), lv, m, a, b, write);
    if (write) TS[lx][ly] += nn; 
    return nn;
  }
  if (m < a) {
    int nn = insert(lx + 1, rch(ly), m + 1, rv, a, b, write);
    if (write) TS[lx][ly] += nn; 
    return nn;
  }
  int nn = insert(lx + 1, lch(ly), lv, m, a, m, write) + insert(lx + 1, rch(ly), m + 1, rv, m + 1, b, write);
  if (write) TS[lx][ly] += nn;
  return nn;
}

void exchange(int a, int b) {
  auto m = QU[a];
  QU[a] = QU[b];
  QU[b] = m;
}

int solve2() {
  memset(TS, 0, sizeof TS);
  inc(i, 1, Q + 1) QU[i] = mt(R[i] - L[i] + 1, L[i], R[i]);
  int mk = INT_MAX, n = 0;
  dec(i, Q, 1) {
    sort(QU + 1, QU + i + 1);
    int vi, li, ri;
    tie(vi, li, ri) = QU[1];
    debug("with case i: %d\n", i);
    debug("vi, li, ri: (%d, %d, %d)\n", vi, li, ri);
    n = insert(0, 0, 1, N, li, ri, true);
    debug("Insert finished, n: %d\n", n);
    mk = min(mk, n);
    exchange(1, i);
    inc (j, 1, i) {
      tie(vi, li, ri) = QU[j];
      debug("inside inc, j: %d\n", j);
      debug("vi, li, ri: (%d, %d, %d)\n", vi, li, ri);
      n = insert(0, 0, 1, N, li, ri, false); 
      debug("Insert finished, n: %d\n", n);
      QU[j] = mt(n, li, ri);
    }
  }
  return mk;
}

int sweep_line() {
  set<int> rs;
  int bl = 0;
  pri pm, cm;
  auto fs = (*hm.begin()).second;
  auto fss = (*fs.begin()).second;
  pm = {0, fss};
  for (auto v: hm) {
    int rk = v.first;
    auto cs = v.second;
    for (auto p: cs) {
      int f = p.first, pk = p.second;
      if (rs.empty()) {
        rs.insert(pk);
        cm = {1, pk};
      } else if (rs.size() == 1) {
        if (f == 0) {
          cm.first += (rk - bl - 1);
          cm.second = *rs.begin();
          rs.insert(pk);
        } else {
          cm.first += (rk - bl);
          if (pm.first < cm.first) pm = {cm.first, pk};
          rs.erase(pk);
          cm = {0, 0};
        }
      } else {
        if (f == 0) rs.insert(pk);
        else {
          rs.erase(pk);
          if (cm.second == pk) {
            if (pm.first < cm.first) pm = cm;
            cm = {0, 0};
          }
        }
      }
      bl = rk;
    }
  }
  // delete
  int mx = pm.first, mr = pm.second;
  int x = QP[mr].first, y = QP[mr].second;
  hm[x].erase(mp(0, mr));
  if (hm[x].empty()) hm.erase(x);
  hm[y].erase(mp(1, mr));
  if (hm[y].empty()) hm.erase(y);
  return mx;
}

void mp_insert(int x, pri v) {
  if (hm[x].empty()) {
    set<pri> s;
    s.insert(v);
    hm[x] = s;
    ++spz;
  } else hm[x].insert(v);
}

int solve3() {
  hm.clear();
  spz = 0;
  inc(i, 1, Q + 1) QP[i] = mp(L[i], R[i]);
  sort(QP + 1, QP + Q + 1);
  inc(i, 1, Q + 1) {
    int x = QP[i].first, y = QP[i].second;
    mp_insert(x, mp(0, i));
    mp_insert(y, mp(1, i));
    //debug("Insert hm: (%d, %d, %d)\n", x, i, 0);
    //debug("Insert hm: (%d, %d, %d)\n", y, i, 1);
  }
  int mk = INT_MAX, fl = 0;
  dec(i, Q, 1) {
    //debug("within turn %d\n", i);
    fl = sweep_line();
    //debug("return fl: %d\n", fl);
    mk = min(mk, fl);
    if (mk == 0) return 0;
  }
  return mk;
}

void setup(pri id, vpri v, int l, int r) {
  if (v.empty()) return;
  debug("setup id: (%d, %d)\n", id.first, id.second);
  // split set
  int m = (l + r) >> 1;
  auto pm = v[m];
  int pc = pm.first;
  debug("point of medium: (%d, %d)\n", pm.first, pm.second);
  set<pri> sm;
  vector<pri> vl, vr;
  vpri ll, lr;
  inc (i, l, r + 1) {
    auto c = v[i];
    int cl = c.first, cr = c.second;
    if (cr < pc) {
      vl.pb(c);
    } else if (pc < cl) {
      vr.pb(c);
    } else {
      sm.insert(c);
      ll.pb(c);
      lr.pb(mp(cr, cl));
    }
  }
  // recursive left
  pri lid = ltp(id), rid = rtp(id);
  setup(lid, vl, 0, vl.size() - 1);
  // recursive right
  setup(rid, vr, 0, vr.size() - 1);
  // tackle current
  sort(vl.begin(), vl.end());
  sort(vr.begin(), vr.end());

  si lcs, rcs;
  if (TM.count(lid)) lcs = gel(TM[lid], 3);
  if (TM.count(rid)) rcs = gel(TM[rid], 3);
  si ns;
  int bg = ll[0].first, ed = (ll.size() == 1) ? pc : ll[1].first;
  inc (i, bg, ed) if (!lcs.count(i)) ns.insert(i);
  bg = (lr.size() == 1) ? pc + 1 : lr[lr.size() - 2].first + 1;
  ed = lr[lr.size() - 1].first;
  inc (i, bg, ed + 1) if (!rcs.count(i)) ns.insert(i);
  TM[id] = mt(sm, ll, lr, ns, pc);
}

void setup_small(pri id, int bg, int ed) {
  if (ed <= bg) return;
  // split set
  int m = (bg + ed) >> 1;
  auto pm = QP[m];
  int pr = pm.second;

  // recursive left
  pri lid = ltp(id), rid = rtp(id);
  setup_small(lid, 0, m - 1);
  // recursive right
  setup_small(rid, m + 1, ed);

  int mr = pr, c = 0, d = 0;

  if (TMS.count(lid)) { 
    mr = max(mr, gel(TMS[lid], 1)); 
    d = max(d, gel(TMS[lid], 3));
  }
  if (TMS.count(rid)) {
    mr = max(mr, gel(TMS[rid], 1)); 
    d = max(d, gel(TMS[rid], 3));
  }
  TMS[id] = mt(pm, mr, c, d);
}

pair<int, pri> search_t(pri id, int x) {
  set<pri> sp = gel(TM[id], 0);
  vpri vl = gel(TM[id], 1);
  vpri vr = gel(TM[id], 2);
  si s = gel(TM[id], 3);
  int m = gel(TM[id], 4);
  if (s.count(x)) {
    if (vl.size() == 1) return {1, vl[0]};
    else {
      if (x < vl[1].first) return {1, vl[0]};
      else return {1, vr[vr.size() - 1]};
    }
  }
  if (x < m) return search_t(ltp(id), x);
  if (m < x) return search_t(rtp(id), x);
  return {0, {0, 0}};
}

void add(pri p, int cnt) {
  pri inid = {0, 0}, id = {0, 0};
  while (TMS.count(id)) {
    pri x;
    int mr, c, d;
    tie(x, mr, c, d) = TMS[id];
    if (x == p) {
      c += cnt;
      if (d < c) {
        d = c;
        while (id != inid) {
          pri fid = fth(id);
          int fd = gel(TMS[fid], 3);
          if (fd < d) fd = d;
          else break;
          id = fid;
        }
      }
      break;
    } else if (p < x) id = ltp(id); 
    else id = rtp(id);
  }
}

pair<int, pri> search_s() {
  pri id = {0, 0};
  while (TMS.count(id)) {
    pri p = gel(TMS[id], 0);
    int c = gel(TMS[id], 2);
    int d = gel(TMS[id], 3);
    if (c == d) return {d, id};
    // test child
    pri lid = ltp(id);
    int ld = gel(TMS[lid], 3);
    if (ld == d) id = lid;
    else id = rtp(id);
  }
  return {0, {0, 0}};
}

void delete_t(pri p) {
  pri id = {0, 0};
  while (TM.count(id)) {
    set<pri>& sp = gel(TM[id], 0);
    int m = gel(TM[id], 4);
    if (sp.count(p)) {
      sp.erase(p);
      vpri& vl = gel(TM[id], 1);
      vpri& vr = gel(TM[id], 2);
      si& s = gel(TM[id], 3);
      int cm = gel(TM[id], 4);
      auto it = lower_bound(vl.begin(), vl.end(), p);
      vl.erase(it);
      it = lower_bound(vr.begin(), vr.end(), mp(p.second, p.first));
      vr.erase(it);
      s.clear();
      pri lid = ltp(id), rid = ltp(id);
      si lcs = gel(TM[lid], 3), rcs = gel(TM[rid], 3);
      if (vl.size() == 1) {
        inc(i, vl[0].first, cm + 1) 
          if (!lcs.count(i)) s.insert(i);
        inc(i, cm + 1, vl[0].second)
          if (!rcs.count(i)) s.insert(i);
      } else if (1 < vl.size()) {
        int rr = vl[1].first;
        inc(i, vl[0].first, rr)
          if (!lcs.count(i)) s.insert(i);
        rr = vr[vr.size() - 2].first + 1;
        inc(i, rr, vr[vr.size() - 1].first)
          if (!rcs.count(i)) s.insert(i);
      }
      return;
    }
    if (p.first < m) id = ltp(id);
    else id = rtp(id);
  }
}

void delete_s(pri p) {
  pri id = {0, 0};
  while (TMS.count(id)) {
    pri& cp = gel(TMS[id], 0);
    if (cp == p) {
      cp = {0, 0};
      return;
    }
    if (p < cp) id = ltp(id);
    else id = rtp(id);
  }
}

int check() {
  for (auto i: insi) {
    auto rs = search_t({0, 0}, i);
    int n = rs.first;
    pri p = rs.second;
    if (n == 1) add(p, 1);
  }
  auto v = search_s();
  delete_t(v.second);
  delete_s(v.second);
  return v.first;
}

int solve4() {
  // sort q
  inc(i, 1, Q + 1) QP[i] = mp(L[i], R[i]);
  sort(QP + 1, QP + Q + 1);
  // set up interval tree
  TM.clear();
  TMS.clear();
  inc(i, 1, Q + 1) invi.pb(QP[i]);
  PR("begin setup interval tree...");
  setup({0, 0}, invi, 0, Q - 1);
  PR("begin setup small interval tree...");
  setup_small({0, 0}, 0, Q - 1);
  PR("after setup interval tree...");
  // search along interval tree
  pri id = {0, 0};
  insi = gel(TM[id], 3);
  int mx = INT_MAX;
  inc (i, 1, Q) {
    PR("before check.");
    PRV(insi);
    int v = check();
    debug("after check, v: %d\n", v);
    if (v == 0) return 0;
    mx = min(mx, v);
  }
  return mx;
}

bool fit(int n) {
  inc (i, 1, Q + 1) {
    LL[i] = QP[i].first;
    RR[i] = -QP[i].second;
    W[i] = LL[i];
  }
  inc (i, 1, Q + 1) {
    int allow = RR[i] + 1;
    int cnt = 0;
    inc (j, i + 1, Q + 1) {
      if (RR[j] <= RR[i]) {
        if (W[i] < LL[j]) {
          cnt += (LL[j] - W[i]);
          if (n <= cnt) {
            allow = LL[j] - (cnt - n);
            break;
          }
        }
        W[i] = max(W[i], RR[j] + 1);
      }
    }
    if (cnt < n) {
      cnt += (RR[i] - W[i] + 1);
      if (cnt < n) return false;
      allow = RR[i] - (cnt - n) + 1;
    }
    inc (j, i + 1, Q + 1) {
      if (allow <= LL[j]) break;
      else if (RR[i] < RR[j]) 
        W[j] = max(W[j], RR[i] + 1);
    }
  }
  return true;
}

int solve() {
  // sort q
  int ml = INT_MAX;
  inc(i, 1, Q + 1) {
    QP[i] = mp(L[i], -R[i]);
    ml = min(ml, R[i] - L[i] + 1);
  }
  sort(QP + 1, QP + Q + 1);
  // bin search
  int d = 0, u = ml;
  while (d < u) {
    int m = (d + u + 1) >> 1;
    if (fit(m)) d = m;
    else u = m - 1;
  }
  return d;
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
    inc(i, 1, Q + 1) scanf("%d %d", &L[i], &R[i]);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

