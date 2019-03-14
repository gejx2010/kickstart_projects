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

#define LARGE 20
#define COMPILE false
#define TESTTIME true
#define DLARGE 2000.0
#define DSMALL 1e-10

// define initial parameters here
int T = 0;
double X[LARGE][LARGE];

double PI = atan(1.0) * 4;

int cut(int n) {
  return n % 3;
}

void add(double* x, double* y, double* a) {
  for (int i = 0; i < 3; ++i) a[i] = (double)(x[i] + y[i]);
}

void sub(double* x, double* y, double* a) {
  for (int i = 0; i < 3; ++i) a[i] = (double)(x[i] - y[i]);
}

void times(double* x, double y, double* a) {
  for (int i = 0; i < 3; ++i) a[i] = (double)(x[i] * y);
}

void div(double* a, double n) {
  for (int i = 0; i < 3; ++i) a[i] /= n;
}

double dis(double* a) {
  return sqrt((double)a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

double multi(double* x, double* y) {
  double res = 0.0;
  for (int i = 0; i < 3; ++i) res += (double)(x[i] * y[i]);
  return res;
}

void cp_hm(double* a, double* l, double* r, double lamb) {
  double rr[3];
  times(r, lamb, rr);
  double ll[3];
  times(l, 1 - lamb, ll);
  add(rr, ll, a);
}

double compute(int h, int l, int r) {
  // first decide md / 6
  double m[3];
  cp_hm(m, X[l], X[r], 0.5);
  PRA(m, 3);
  double ml[3];
  cp_hm(ml, X[l], m, 1 / 3.0);
  double mr[3];
  cp_hm(mr, X[r], m, 1 / 3.0);
  double low[3];
  sub(X[l], m, low);
  double slo[3];
  sub(X[h], m, slo);
  double slol[3];
  sub(X[h], ml, slol);
  double slor[3];
  sub(X[h], mr, slor);
  PRA(low, 3);
  double dlow = dis(low);
  double dslo = dis(slo);
  double dslol = dis(slol);
  double dslor = dis(slor);
  PR(dslo);
  PR(dslol);
  PR(dslor);
  PR(dlow / 3);
  PR(dslo < dlow / 3);
  if (dslo < dlow / 3 || dslol < dlow / 3 || dslor < dlow / 3) return dlow / 3;
  // compute (h --- m)
  PR("Case 1:");
  double res = DBL_MAX;
  double xx2 = multi(low, slo) * multi(low, slo) / multi(low, low);
  double yy2 = multi(slo, slo) - xx2;
  double aa = 8, bb = 2;
  double cc = -1 - (multi(low, low) - 9 * xx2) / yy2;
  double dd = bb * bb - 4 * aa * cc;
  PR(dis(low));
  PR(xx2);
  PR(yy2);
  PR(cc);
  PR(dd);
  double k = 0.0;
  if (multi(low, low) + yy2 < 9 * xx2) {
    res = xx2;
  } else if (0 <= dd) {
    k = (-bb + sqrt(dd)) / (2 * aa);
    PR(k);
    res = sqrt(xx2 + k * k * yy2);
  }
  // compute (h -- l or h -- r)
  PR("Case 2:");
  if (dslol < dslor) {
    cp_hm(m, X[l], X[h], 0.5);
    sub(X[h], m, low);
    sub(X[r], m, slo);
  } else {
    cp_hm(m, X[r], X[h], 0.5);
    sub(X[h], m, low);
    sub(X[l], m, slo);
  }
  // compute another case
  xx2 = multi(low, slo) * multi(low, slo) / multi(low, low);
  yy2 = multi(slo, slo) - xx2;
  aa = 24.0, bb = - 50.0;
  cc = 25 - (xx2 - 25 * multi(low, low)) / yy2;
  dd = bb * bb - 4 * aa * cc;
  PR(dis(low));
  PR(xx2);
  PR(yy2);
  PR(cc);
  PR(dd);
  if (multi(slo, slo) < 25 * multi(low, low)) {
    res = min(res, dis(low));
  } else if (0 <= dd) {
    double k1 = (-bb + sqrt(dd)) / (2 * aa);
    double k2 = (-bb - sqrt(dd)) / (2 * aa);
    if (0 < k2) k = k2;
    else k = k1;
    PR(k);
    res = min(res, sqrt(xx2 + k * k * yy2) / 5);
  }
  PR(res);
  return res;
}

double facos(double v) {
  if (1 < v) return 0;
  if (v < -1) return PI;
  return acos(v);
}

bool detect(double rh, double dhl, double rl, double dhr, double rr, double* hl, double* hr) {
  double thl = (rh * rh + dhl * dhl - rl * rl) / (2 * rh * dhl);
  PR(thl);
  double vthl = facos(thl);
  PR(vthl);
  double thr = (rh * rh + dhr * dhr - rr * rr) / (2 * rh * dhr);
  PR(thr);
  double vthr = facos(thr);
  PR(vthr);
  double tlr = multi(hl, hr) / (dhl * dhr);
  PR(tlr);
  double vtlr = facos(tlr);
  PR(vtlr);
  return vtlr < vthl + vthr;
}

bool interset(int h, double rh, int l, double rl, int r, double rr) {
  double hl[3], lr[3], hr[3];
  sub(X[h], X[l], hl);
  sub(X[h], X[r], hr);
  sub(X[l], X[r], lr);
  double dhl = dis(hl);
  double dhr = dis(hr);
  double dlr = dis(lr);
  PR(rh);
  PR(rl);
  PR(rr);
  PR(dhl);
  PR(dhr);
  PR(dlr);
  if (rh + rl < dhl) return false;
  if (rh + rr < dhr) return false;
  if (rl + rr < dlr) return false;
  if (dhl < abs(rh - rl)) {
    bool res = (rl < rh && dlr < rl + rr) || (rh < rl && dhr < rh + rr);
    return res;
  }
  if (dhr < abs(rh - rr)) {
    bool res = (rh < rr && dhl < rh + rl) || (rr < rh && dlr < rr + rl);
    return res;
  }
  if (dlr < abs(rl - rr)) {
    bool res = (rl < rr && dhl < rl + rh) || (rr < rl && dhr < rh + rr);
    return res;
  }
  double nhl[3];
  times(hl, -1, nhl);
  if (detect(rh, dhl, rl, dhr, rr, hl, hr) ||
      detect(rl, dhl, rh, dlr, rr, nhl, lr) ||
      detect(rr, dhr, rh, dlr, rl, hr, lr))
    return true;
  return false;
}

double bs2(int h, int l, int r) {
  double bres = DLARGE, nres = 0, m = 0.0;
  while (true) {
    m = (bres + nres) / 2;
    PR("bs2");
    PR(m);
    if (bres - nres < DSMALL) break;
    else if (interset(h, m * 5, l, m, r, m)) bres = m; 
    else nres = m;
  }
  return m;
}

double bs1(int h, int l, int r) {
  double bres = DLARGE, nres = 0, m = 0.0;
  while (true) {
    m = (bres + nres) / 2;
    PR("bs1");
    PR(m);
    if (bres - nres < DSMALL) break;
    else if (interset(h, m, l, m * 3, r, m * 3)) bres = m;
    else nres = m;
  }
  return m;
}

double solve4() {
  double res = DBL_MAX;
  res = min(res, bs1(0, 1, 2));
  res = min(res, bs1(1, 2, 0));
  res = min(res, bs1(2, 0, 1));
  res = min(res, bs2(0, 1, 2));
  res = min(res, bs2(1, 2, 0));
  res = min(res, bs2(2, 0, 1));
  return res;
}

double solve3() {
  double a[3];
  double md = 0;
  double mk = 0;
  rep(i,0,3) {
    sub(X[i], X[cut(i + 1)], a);
    double d = dis(a);
    if (md < d) {
      md = d;
      mk = cut(i + 2);
    }
  }
  PR("solve3:");
  PR(mk);
  return compute(mk, cut(mk + 1), cut(mk + 2));
}

double solve2() {
  double res = compute(0, 1, 2);
  res = min(res, compute(1, 2, 0));
  res = min(res, compute(2, 0, 1));
  return res;
}

double solve() {
  double a = abs(X[0][0] - X[1][0]);
  double b = abs(X[1][0] - X[2][0]);
  double c = abs(X[2][0] - X[0][0]);
  return max(max(a / 6, b / 6), c / 6);
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
    for (int j = 0; j < 3; ++j)
      for (int k = 0; k < 3; ++k) {
        scanf("%lf", &X[j][k]);
      }
    double r = solve4();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %.10f\n", i, r);
  }
  return 0;
}

