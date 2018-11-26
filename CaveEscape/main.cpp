#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stack>
#include <map>
#include <bitset>

#define PR(x) cerr << #x << ": " << x << endl;
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define PRV(x) cerr << #x << ": " << endl; for (auto& it: (x)) { cerr << (it) << " "; } \
    cerr << endl;

using namespace std;

#define LARGE 1000
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, M, E, SR, SC, TR, TC;
int ini_array[LARGE][LARGE];
int trace[LARGE][LARGE];
int vrank;
int erank;
int mask;
const int MASK_LEN = 17;
map<pair<int, int>, int> key_map;
map<pair<int,int>, int> tr;
map<int, pair<int, int>> pos_map;
map<int, int> leave_energy;
map<int, int> reach_target;
map<int, int> mask_traced;

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

bool is_obstacle(int r, int l) {
  return (ini_array[r][l] == -100000);
}

bool is_trap(int r, int l) {
  return (!is_obstacle(r, l) && ini_array[r][l] < 0);
}

bool is_normal(int r, int l) {
  return (ini_array[r][l] == 0);
}

bool is_potion(int r, int l) {
  return (0 < ini_array[r][l]);
}

bool is_target(int r, int l) {
  return (r == TR - 1 && l == TC - 1);
}

bool is_traced(int r, int l) {
  return (0 <= trace[r][l]);
}

vector< pair<int, int> > direction(int r, int l) {
  vector< pair<int, int> > res;
  if (0 < r) res.pb(mp(r - 1, l));
  if (0 < l) res.pb(mp(r, l - 1));
  if (r < N - 1) res.pb(mp(r + 1, l));
  if (l < M - 1) res.pb(mp(r, l + 1));
  return res;
}

int trace_full(int mask, int r, int l, vector<pair<int, int>> &ca, map<pair<int, int>, int> &tr) {
  int pot = 0;
  if (is_target(r, l)) {
    if(COMPILE) printf("At (%d, %d), result reach.\n", r, l);
    reach_target[mask] = 1;
  }
  for (auto& dir: direction(r, l)) {
    if (is_obstacle(dir.first, dir.second)) {
      continue;
    } else if (is_traced(dir.first, dir.second)) {
      continue;
    } else {
      trace[dir.first][dir.second] = 1;
      ca.pb(mp(dir.first, dir.second));
      if (is_trap(dir.first, dir.second)) tr[mp(dir.first, dir.second)] = 1;
      else {
        pot += ini_array[dir.first][dir.second];
        pot += trace_full(mask, dir.first, dir.second, ca, tr);
      }
    } 
  }
  return pot;
}

int trace_cave(int mask, int ckey, map<pair<int, int>, int> tr) {
  if (COMPILE) cout << "mask:" << bitset<sizeof(int)*8>(mask) << endl;
  if (mask_traced.count(mask)) {
    if (COMPILE) printf("mask %d is in mask_traced, with value: %d\n", mask, mask_traced[mask]);
    return mask_traced[mask];
  }
  int res = -1;
  auto pos = pos_map[ckey];
  int r = pos.first, l = pos.second;
  if (COMPILE) { printf("mask %d stands (%d, %d)\n", mask, r, l); }
  if (leave_energy[mask] + ini_array[r][l] < 0) return res;
  // get ca, tr & new e;
  vector<pair<int, int>> ca;
  trace[r][l] = 1;
  ca.pb(mp(r, l));
  int pot = trace_full(mask, r, l, ca, tr);
  if (COMPILE) printf("mask %d get pot %d\n", mask, pot);
  // set leave_energy
  leave_energy[mask] += ini_array[r][l] + pot;
  if (COMPILE) printf("mask %d, reach_target: %d\n", mask, reach_target[mask]);
  if (reach_target[mask]) res = leave_energy[mask];
  for (auto& it: tr) {
    int pr = it.first.first, pl = it.first.second;
    int key = key_map[mp(pr, pl)];
    int new_mask = mask + (1 << key);
    decltype(tr) ntr(tr);
    ntr.erase(it.first);
    if (COMPILE) printf("mask %d, (%d, %d): %d, new_mask: %d\n", mask, pr, pl, key, new_mask);
    leave_energy[new_mask] = leave_energy[mask];
    reach_target[new_mask] = reach_target[mask];
    res = max(res, trace_cave(new_mask, key, ntr));
  }
  // clean ca
  for (auto& it: ca) {
    trace[it.first][it.second] = -1;
  }
  mask_traced[mask] = res;
  if (COMPILE) printf("mask %d, (%d, %d) mask_traced set to true, with res: %d\n", mask, r, l, res);
  return res;
}

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
    scanf("%d %d %d %d %d %d %d", &N, &M, &E, &SR, &SC, &TR, &TC);
    if (COMPILE) printf("%d %d %d %d %d %d %d\n", N, M, E, SR, SC, TR, TC);
    for (int j = 0; j < N; j++) 
      for (int k = 0; k < M; k++) 
        scanf("%d", &ini_array[j][k]);
    // initialize
    memset(trace, -1, sizeof(trace));
    key_map.clear();
    pos_map.clear();
    leave_energy.clear();
    reach_target.clear();
    mask_traced.clear();
    tr.clear();
    // setup key_map
    int cnt = 0;
    key_map[mp(SR - 1, SC - 1)] = cnt++;
    pos_map[0] = mp(SR - 1, SC - 1);
    if (COMPILE) printf("key_map, (%d, %d): %d\n", SR - 1, SC - 1, cnt - 1);
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < M; k++) {
        if (is_trap(j, k)) {
          key_map[mp(j, k)] = cnt;
          pos_map[cnt++] = mp(j, k);
          if (COMPILE) printf("key_map, (%d, %d): %d\n", j, k, cnt - 1);
        }
      }
    }
    // mask set to 0 to search
    mask = 0;
    leave_energy[mask] = E;
    int res = trace_cave(mask, 0, tr);
    if (COMPILE) printf ("res: %d\n", res);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
