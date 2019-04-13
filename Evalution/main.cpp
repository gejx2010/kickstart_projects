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
#define PRV(x) cout << #x << ": "; for (auto& it: x) cout << it << ' '; cout << endl;
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
#define COMPILE false
#define TESTTIME true

// define initial parameters here
int T = 0;
int N;
string V[LARGE];
map<string, vector<string>> eqa;
map<string, bool> vrm;

bool search() {
  bool upd = true;
  while (upd) {
    upd = false;
    for (auto v: eqa) {
      auto s = v.first;
      auto val = v.second;
      if (vrm[s]) continue;
      if (val.empty()) {
        vrm[s] = upd = true;
        continue;
      }
      bool can = true;
      for (auto n: val) 
        if (!vrm[n]) can = false;
      if (can) vrm[s] = upd = true;
    } 
  }
  for (auto n: vrm) if (!n.second) return false;
  return true;
}

string solve() {
  eqa.clear();
  vrm.clear();
  // get string
  inc (i, 1, N + 1) {
    string s, cs;
    vector<string> ss;
    for (int j = 0; V[i][j] != '\0'; ++j) {
      if (V[i][j] == '=') {
        cs = s;
        vrm[s] = false;
        s = "";
      } else if (V[i][j] == ',') {
        ss.pb(s);
        vrm[s] = false;
        s = "";
      } else if (V[i][j] == ')' && (!s.empty())) {
        vrm[s] = false;
        ss.pb(s);
        s = "";
      } else if (V[i][j] == '(') {
        s = "";
      } else {
        s += V[i][j];
      }
    }
    eqa[cs] = ss;
    //PR(cs);
    //PRV(eqa[cs]);
  }
  //PRM(vrm);
  bool r = search();
  if (r) return "GOOD";
  else return "BAD";
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
    inc (i, 1, N + 1) cin >> V[i];
    string r = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %s\n", i, r.c_str());
  }
  return 0;
}

