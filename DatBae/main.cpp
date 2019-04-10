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

#define LARGE 2001
#define SMALL 20
#define COM 16
#define COMPILE false
#define TESTTIME false

#define lch(x) ((x) << 1)
#define rch(x) (((x) << 1) + 1)

// define initial parameters here
int T = 0;
int N, B, F;
char S[LARGE];
char rsp[LARGE];
char ans[LARGE];
int nrsp;

struct GS {
  int state;
  int st;
  int ed;
  int nb;
  string s;
  GS() { state = st = ed = nb = 0; s = ""; }
  GS(int a, int b, int c) : st(a), ed(b), nb(0), state(c), s("") {}
};

GS sg[SMALL][LARGE];
int sgz;

void build_tree(int lx, int ly, int st, int ed) {
  if (ed < st) return;
  sg[lx][ly] = GS(st, ed, 0);
  if (st == ed) return;
  int m = (st + ed) >> 1;
  int lh = lch(ly), rh = rch(ly);
  build_tree(lx + 1, lh, st, m);
  build_tree(lx + 1, rh, m + 1, ed);
}

string make_str(int st, int ed, int c) {
  string s = "";
  inc (i, st, ed) {
    S[i] = '0' + c;
    s += '0' + c;
  }
}

void setup() {
  sgz = 0;
  bool tn = true;
  while (sgz * COM + 1 < N) {
    int st = sgz * COM + 1, ed = min((sgz + 1) * COM, N);
    build_tree(0, sgz, st, ed);
    if (tn) make_str(st - 1, ed, 1);
    else make_str(st - 1, ed, 0);
    ++sgz;
  }
  S[N] = '\0';
}

void test_tree(int lx, int ly, int nb) {
  int x = sg[lx][ly].st, y = sg[lx][ly].ed;
  int n = y - x + 1;
  sg[lx][ly].nb = nb;
  if (nb == 0) {
    sg[lx][ly].s = make_str(x - 1, y, 0);
    sg[lx][ly].state = 5;
  } else if (nb == n) {
    sg[lx][ly].s = make_str(x - 1, y, 1);
    sg[lx][ly].state = 5;
  } else {
    int m = (x + y) >> 1;
    make_str(x - 1, m, 1);
    make_str(m, y, 0);
    sg[lx][ly].state = 1;
  }
}

void ana_tree() {
  int n = 0, len = strlen(rsp);
  bool tn = true;
  int cnt = 0;
  int rk = 0;
  while (rk < sgz) {
    int lv = sg[0][rk].st, rv = sg[0][rk].ed;
    if (tn) {
      cnt = 0;
      while (rsp[n] == '1') ++cnt, ++n;
    } else {
      cnt = 0;
      while (rsp[n] == '0') { ++cnt, ++n; }
    }
    test_tree(0, rk, (rv - lv + 1) - cnt); 
    tn = !tn;
    ++rk;
  }
}

void sub_search(int lx, int ly, int l, int r) {
  int se = sg[lx][ly].state;
  int lv = sg[lx][ly].st, rv = sg[lx][ly].ed;
  if (se == 1) {
    int cnt = 0;
    inc (i, l, r) if (rsp[i] == '1') ++cnt;
    test_tree(lx + 1, lch(ly), cnt);
    test_tree(lx + 1, rch(ly), r - l - cnt);
    sg[lx][ly].state = 2;
  } else if (se == 2) {
    int cst = sg[lx + 1][lch(ly)].st;
    int ced = sg[lx + 1][lch(ly)].ed;
    int cnb = sg[lx + 1][lch(ly)].nb;
    int cv = (ced + 1 - cst) - cnb;
    sub_search(lx + 1, lch(ly), l, l + cv);
    sub_search(lx + 1, rch(ly), l + cv, r);
  } else if (se == 5) {
    make_str(lv - 1, rv, 0);
  }
}

void search_tree() {
  int bf = 0, ak = 0, rk = 0;
  while (rk < sgz) {
    int lv = sg[0][rk].st, rv = sg[0][rk].ed, nb = sg[0][rk].nb;
    int vn = (rv + 1 - lv) - nb;
    ak += vn;
    sub_search(0, rk, bf, ak);
    bf = ak;
    ++rk;
  }
}

bool test_finish(int lx, int ly) {
  if (sg[lx][ly].state == 5) return true;
  if (sg[lx + 1][lch(ly)].state == 5 &&
      sg[lx + 1][rch(ly)].state == 5) {
    sg[lx][ly].s = sg[lx + 1][lch(ly)].s + sg[lx + 1][rch(ly)].s;
    sg[lx][ly].state = 5;
    return true;
  }
  return test_finish(lx + 1, lch(ly)) && test_finish(lx + 1, rch(ly));
}

bool finish() {
  int rk = 0;
  bool fin = false;
  while (rk < sgz) {
    if (!test_finish(0, rk)) return false;
  }
  return true;
}

string merge() {
  int rk = 0;
  string s = "";
  while (rk < sgz) {
    s += sg[0][rk].s;
    ++rk;
  }
  return s;
}

void solve() {
  memset(sg, 0, sizeof sg);
  cin >> N >> B >> F;
  setup();
  int fc = 0;
  while (fc < F) {
    cout << S << endl;
    cin >> rsp;
    if (fc == 0) ana_tree();
    else search_tree();
    if (finish()) {
      string s = merge();
      inc (i, 0, N) if (s[i] == '1') cout << i << ' ';
      cout << endl;
      cin >> rsp;
      break;
    }
    ++fc;
  }
}

int main(int argc, char** argv) {
  cin >> T;
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
  }
  return 0;
}

