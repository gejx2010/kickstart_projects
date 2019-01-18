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
#define PRA(x,sz) cout << #x << ": " << endl; for (int x##_it = 0; x##_it < (sz); ++(x##_it)) cout << (x)[x##_it] << " "; cout << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)
#define num(x) ((x) - 'A')

#define LARGE 100
#define COMPILE false
#define TESTTIME false
#define CLEN 26

// define initial parameters here
int T = 0, L = 0;
char A[LARGE], B[LARGE];

class TN {
public:
  int value;
  vector<TN*> childs;
  TN() { value = 0; childs.clear(); }
  ~TN() { for (auto& it: childs) delete it; childs.clear(); }
} *root;

int find(TN* p, int num) {
  for (int i = 0; i < p->childs.size(); ++i) 
    if (p->childs[i]->value == num) return i;
  return -1;
}

void insert_tree(int* a) {
  TN* cp = root;
  for (int i = 0; i < CLEN; ++i) {
    int ind = find(cp, a[i]);
    if (ind < 0) {
      ind = cp->childs.size();
      TN* np = new TN;
      np->value = a[i];
      cp->childs.pb(np);
    }
    cp = cp->childs[ind];
  }
}

void visit(char* a) {
  int alp[CLEN];
  for (int i = 0; i < L; ++i) {
    memset(alp, 0, sizeof alp);
    for (int j = i; j < L; ++j) {
      ++alp[num(a[j])];
      insert_tree(alp);
    }
  }
}

int search(int* a) {
  TN* cp = root;
  for (int i = 0; i < CLEN; ++i) {
    int ind = find(cp, a[i]);
    if (ind < 0) return 0;
    cp = cp->childs[ind];
  }
  return 1;
}

int solve() {
  delete root;
  root = new TN;
  // visit on B
  visit(B);
  // query for A
  int alp[CLEN];
  int cnt = 0;
  for (int i = 0; i < L; ++i) {
    memset(alp, 0, sizeof alp);
    for (int j = i; j < L; ++j) {
      ++alp[num(A[j])];
      cnt += search(alp);
    }
  }
  return cnt;
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
    scanf("%d", &L);
    scanf("%s", A);
    scanf("%s", B);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

