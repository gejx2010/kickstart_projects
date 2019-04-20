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
#define PRV(x) cerr << #x << ": "; for (auto& xit: x) cerr << xit << ' '; cerr << endl;
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

#define LARGE 2001
#define SMALL 101
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int N;
char W[LARGE][SMALL];
string ms[LARGE];

multimap<int, pair<string, string>> sm;
map<string, int> ex;
set<string> sel;

int cmp_suffix(int l, int r) {
  int ls = strlen(W[l]), rs = strlen(W[r]);
  int res = 0;
  inc (i, 1, min(ls, rs) + 1) {
    if (W[l][ls - i] != W[r][rs - i]) break;
    else ++res;
  }
  return res;
}

int cnt_str(string s) {
  int cnt = 0;
  inc (i, 1, N + 1) {
    string w = W[i];
    if (ex[w] && string::npos != w.find(s)) ++cnt;
  }
  return cnt;
}

void try_del(string s) {
  //PR("try_del");
  //PR(s);
  inc (i, 1, N + 1) {
    string w = W[i];
    //PR(w);
    //PR(w.find(s));
    if (string::npos != w.find(s)) ex[w] = 0;
  }
}

int solve() {
  sm.clear();
  ex.clear();
  // build ex
  inc (i, 1, N + 1) ex.insert({W[i], 1});
  inc (i, 1, N + 1) {
    string cs = W[i];
    int ml = 0;
    inc (j, i + 1, N + 1) {
      string ds = W[j];
      int n = cmp_suffix(i, j);
      //PR(n);
      //PR(cs);
      //PR(ds);
      sm.insert({n, {cs, ds}});
    }
  }
  // loop
  auto it = sm.end();
  int res = 0;
  sel.clear();
  //PR("begin loop.");
  while (it != sm.begin()) {
    --it;
    int n = it->first;
    auto cs = it->second;
    string ls = cs.first, rs = cs.second;
    //PR(n);
    //PR(ls);
    //PR(rs);
    if (ex[ls] && ex[rs] && n != 0) {
      string suf = ls.substr(ls.length() - n);
      //PR(suf);
      if (sel.count(suf)) {
        if (1 < n) {
          sm.insert({n - 1, {ls, rs}});
        }
      } else if (suf.length() != 0) {
        res += 2;
        ex[ls] = ex[rs] = 0;
        sel.insert(suf);
      }
    }
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
    cin >> N;
    inc (j, 1, N + 1) cin >> W[j];
    int r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, r);
  }
  return 0;
}

