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

#define PR(x) cerr << #x << ": " << x << endl;
#define mp make_pair
#define mt make_tuple
#define pb push_back

using namespace std;

#define LARGE 200
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0, N = 0, P = 0;
string ini_array[LARGE];
multimap<int, string> pmap;

class ST {
public:
  bool is_leaf;
  ST *left, *right;
  ST() { is_leaf = false; left = nullptr, right = nullptr; }
};

class STT {
public:
  ST* root;
  STT() { root = new ST; }
  
  void insert(string m) {
    ST* cp = root;
    for (int i = 0; i < m.length(); i++) {
      if (m[i] == 'R') {
        if (cp->left == nullptr) {
          cp->left = new ST;
          cp = cp->left;
        } else {
          cp = cp->left;
          if (cp->is_leaf) return;
        }
      } else {
        if (cp->right == nullptr) {
          cp->right = new ST;
          cp = cp->right;
        } else {
          cp = cp->right;
          if (cp->is_leaf) return;
        }
      }
    }
    cp->is_leaf = true;
  }

  void view(ST* c, long long& cnt, int deep) {
    if (c == nullptr) return;
    if (c->is_leaf) {
      long long v = 1;
      v <<= (N - deep);
      PR(v);
      PR(deep);
      cnt += v;
    } else {
      view(c->left, cnt, deep + 1);
      view(c->right, cnt, deep + 1);
    }
  }

  long long trace() {
   long long cnt = 0;
   view(root, cnt, 0);
   PR(cnt);
   return cnt;
  }
};

void printf_array(void* a, int num, char* name, char* type="int") {
  printf("Begin print content of %s:\n", name);
  int* b = NULL;
  long long* c = NULL;
  if (strcmp(type, "int") == 0) b = (int*)a; 
  else c = (long long*)a;
  for (int k = 0; k < num; k++) {
    if (strcmp(type, "int") == 0) printf("%d ", b[k]);
    else printf("%lld ", c[k]);
  }
  printf("\nAfter print content of %s.\n", name);
}
#define PRA(a, num, name, type) printf_array(a, num, name, type)

int main(int argc, char** argv) {
  char* def_ifn = "large.in";
  char* def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn, "r", stdin);
  freopen(def_ofn, "w", stdout);
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) printf("With Case %d.\n", i);
    scanf("%d %lld", &N, &P);
    PR(N);
    PR(P);
    int j = 0;
    STT* tr = new STT;
    while (j < P) {
      cin >> ini_array[j];
      tr->insert(ini_array[j]);
      j++;
    }
    long long res = 1 << N;
    long long has = tr->trace();
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %lld\n", i, res - has);
  }
  return 0;
}
