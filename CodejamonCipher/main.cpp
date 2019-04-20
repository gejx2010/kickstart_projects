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

#define LARGE 4001
#define COMPILE false
#define TESTTIME true
#define COM 26
#define MAX_LEN 20
#define MOD 1000000007

#define num(x) ((x) - 'a' + 1)

// define initial parameters here
int T = 0;
int V, S;
string W[LARGE];
string E[LARGE];
map<map<int, int>, int> voc;
map<int, int> imap;
ll DP[LARGE];

void ini_map() {
  inc (i, 1, COM + 1) imap[i] = 0;
}

void try_ins(map<int, int> m) {
  if (voc.count(m)) ++voc[m];
  else voc[m] = 1;
}

void init_words() {
  voc.clear();
  inc (i, 1, V + 1) {
    map<int, int> m = imap;
    inc (j, 0, W[i].length()) ++m[num(W[i][j])];
    try_ins(m);
  }
  //for (auto n: voc) {
  //  auto f = n.first;
  //  auto s = n.second;
  //  PRM(f);
  //  PR(s);
  //}
}

ll solve(int rk) {
  printf("Case #%d:", rk);
  init_words();
  inc (i, 1, S + 1) {
    DP[0] = 1;
    //PR(E[i]);
    int cl = E[i].length();
    //PR(cl);
    inc (j, 0, cl) {
      DP[j + 1] = 0;
      map<int, int> m = imap;
      int lb = max(0, j - MAX_LEN + 1);
      dec (k, j, lb) {
        //PR(i);
        //PR(j);
        //PR(k);
        ++m[num(E[i][k])];
        //PRM(m);
        //PR(voc.count(m));
        if (voc.count(m)) {
          ll v = (DP[k] * voc[m]) % MOD;
          DP[j + 1] = (DP[j + 1] + v) % MOD;
        }
      } 
      //PR(DP[j + 1]);
    }
    printf(" %lld", DP[cl]);
  }
  printf("\n");
}

int main(int argc, char** argv) {
  string def_ifn = "large.in";
  string def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn.c_str(), "r", stdin);
  freopen(def_ofn.c_str(), "w", stdout);
  ini_map();
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) cerr << "Within Case " << i << ".\n";
    cin >> V >> S;
    inc (j, 1, V + 1) cin >> W[j];
    inc (j, 1, S + 1) cin >> E[j];
    solve(i);
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
  }
  return 0;
}

