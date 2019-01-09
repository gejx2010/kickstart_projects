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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pri;
typedef pair<ll,ll> prl;
typedef tuple<int,int,int> tpi;
typedef tuple<ll,ll,ll> tpl;
typedef vector<int> vi;
typedef vector<pri> vpri;

#define PR(x) cerr << #x << ": " << (x) << endl;
#define PRA(x,sz) cerr << #x << ": " << endl; for (int x##_it = 1; x##_it <= (sz); ++(x##_it)) cerr << (x)[x##_it] << " "; cerr << endl;
#define PRV(x) cerr << #x << ": "; for (auto& x##_it: x) cerr << x##_it << ' '; cerr << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i,a,b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define gel(x,i) get<(i)>(x)

#define LARGE 200
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N, M, P;
char fri[LARGE][LARGE], fbd[LARGE][LARGE];
char ori[LARGE];
int bias[LARGE];
int ori_bias;
multimap<int, string> hm;

bool not_exist(const char* ori) {
  for (int i = 0; i < M; ++i) {
    if (strcmp(ori, fbd[i]) == 0)
      return false;
  }
  return true;
}

char change(char a) {
  if (a == '0') return '1';
  else return '0';
}

int solve() {
  // find original closest strings
  ori_bias = 0;
  for (int i = 0; i < P; ++i) {
    int cz = 0, co = 0;
    for (int j = 0; j < N; ++j) {
      if (fri[j][i] == '0') ++cz;
      else ++co;
    }
    if (co <= cz) { 
      ori[i] = '0'; 
      ori_bias += co; 
      bias[i] = cz - co;
    } else { 
      ori[i] = '1'; 
      ori_bias += cz; 
      bias[i] = co - cz;
    }
  }
  ori[P] = '\0';
  PR(ori);
  PR(ori_bias);
  if (not_exist(ori)) return ori_bias;
  // huffman strings
  string nst(ori);
  int cur_bias = ori_bias;
  hm.clear();
  while (true) {
    // base on last choice, insert new item into map
    for (int i = 0; i < P; ++i) {
      if (nst[i] == ori[i]) {
        string cnst(nst);
        PR(cnst);
        cnst[i] = change(nst[i]);
        PR(cnst);
        hm.insert({cur_bias + bias[i], cnst});
      }
    }
    // select new choice from map
    auto it = hm.begin();
    cur_bias = (*it).first;
    nst = (*it).second;
    hm.erase(it);
    PR(nst);
    PR(cur_bias);
    if (not_exist(nst.c_str())) return cur_bias;
  }
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
    scanf("%d %d %d", &N, &M, &P);
    for (int j = 0; j < N; ++j) scanf("%s", &fri[j]);
    for (int j = 0; j < M; ++j) scanf("%s", &fbd[j]);
    int res = solve();
    clock_t rt = clock();
    if (TESTTIME) cerr << "Solve case takes time:" << ((float)(rt - st)) / CLOCKS_PER_SEC << " seconds.\n";
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

