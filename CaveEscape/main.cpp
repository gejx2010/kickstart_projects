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

#define LARGE 200
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, M, E, SR, SC, TR, TC;
int ini_array[LARGE][LARGE];
const int MASK_LEN = 17;
int cnt_len = 0;
map<pair<int, int>, int> key_map;
map<int, pair<int, int>> pos_map;
map<int, int> leave_energy;
map<int, int> reach_target;
map<int, int> unvisited;
map<int, int> mask_traced;
int traced[LARGE][LARGE];
int area[LARGE];
int area_array[LARGE][LARGE];
int area_potion[LARGE * LARGE];
int area_number = 0;

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
  return 0 < traced[r][l];
}

vector< pair<int, int> > direction(int r, int l) {
  vector< pair<int, int> > res;
  if (0 < r) res.pb(mp(r - 1, l));
  if (0 < l) res.pb(mp(r, l - 1));
  if (r < N - 1) res.pb(mp(r + 1, l));
  if (l < M - 1) res.pb(mp(r, l + 1));
  return res;
}

void trace_full(int mask, int r, int l) {
  traced[r][l] = 1;
  if (is_target(r, l)) reach_target[mask] = 1;
  for (auto& dir: direction(r, l)) {
    if (is_obstacle(dir.first, dir.second) || is_traced(dir.first, dir.second)) {
      continue;
    } else if (is_trap(dir.first, dir.second)) {
      unvisited[mask] |= (1 << key_map[mp(dir.first, dir.second)]);
    } else {
      trace_full(mask, dir.first, dir.second);
    }
  }
}

void trace_each_point(int r, int l) {
  if (area_array[r][l] != 0) return;
  if (is_normal(r, l) || is_potion(r, l)) {
    area_array[r][l] = area_number;
    area_potion[area_number] += ini_array[r][l];
  } else if (is_trap(r, l)) {
    int k = key_map[mp(r, l)];
    area[area_number] |= (1 << k);
    return;
  } else if (is_obstacle(r, l)) return;
  for (auto& t: direction(r, l)) {
    trace_each_point(t.first, t.second); 
  }
}

void trace_area() {
  area_number = 1;
  for (int i = 0; i < N; i++) 
    for (int j = 0; j < M; j++) {
      if ((is_normal(i, j) || is_potion(i, j)) && area_array[i][j] == 0) {
        trace_each_point(i, j);
        area_number++;
      }
    }
  int an = area_array[SR - 1][SC - 1];
  area[an] |= 1;
}

void get_potion(int r, int l, int new_mask, int cmask) {
  int tmask = new_mask;
  int tt[] = {0, 0, 0, 0};
  int i = 0;
  for (auto& t: direction(r, l)) {
    if (is_obstacle(t.first, t.second) || is_trap(t.first, t.second)) continue;
    int an = area_array[t.first][t.second];
    bool has_added = false;
    for (int j = 0; j < i; j++) 
      if (tt[j] == an) {
        has_added = true;
        break;
      }
    if (has_added) continue;
    tt[i++] = an;
    if (COMPILE) printf("next r: %d, l: %d, an: %d, area: %d, tmask: %d, cmask: %d\n", t.first, t.second, an, area[an], tmask, cmask);
    if ((area[an] & tmask) == cmask) {
      leave_energy[new_mask] += area_potion[an];
      tmask |= area[an];
      if (COMPILE) printf("leave_energy[%d] become %d\n", new_mask, leave_energy[new_mask]);
    }
  }
  if (COMPILE) printf("leave_energy[%d]: %d\n", new_mask, leave_energy[new_mask]);
}

int trace_cave(int mask) {
  if (mask_traced.count(mask)) {
    if (COMPILE) printf("mask %d is in mask_traced, with value: %d\n", mask, mask_traced[mask]);
    return mask_traced[mask];
  }
  int res = -1;
  if (COMPILE) cout << "mask:" << bitset<sizeof(int)*8>(mask) << endl;
  if (reach_target[mask]) {
    res = leave_energy[mask];
    if (COMPILE) printf("target has reached, with leave_energy: %d\n", res);
  }
  for (int i = 0; i < cnt_len; i++) {
    int cmask = (1 << i);
    if (COMPILE) cout << "cmask:" << bitset<sizeof(int)*8>(cmask) << endl;
    if (COMPILE) cout << "unvisited:" << bitset<sizeof(int)*8>(unvisited[mask]) << endl;
    if (COMPILE) cout << "mask & cmask:" << bitset<sizeof(int)*8>(mask & cmask) << endl;
    if (COMPILE) cout << "unvisited & cmask:" << bitset<sizeof(int)*8>(unvisited[mask] & cmask) << endl;
    if ((mask & cmask) == 0 && (unvisited[mask] & cmask) != 0) {
      int new_mask = (mask | cmask);
      if (COMPILE) printf("unvisited: %d\n", i);
      if (COMPILE) cout << "new_mask:" << bitset<sizeof(int)*8>(new_mask) << endl;
      auto pos = pos_map[i];
      int r = pos.first, l = pos.second;
      leave_energy[new_mask] = leave_energy[mask] + ini_array[r][l];
      if (0 <= leave_energy[new_mask]) {
        reach_target[new_mask] = reach_target[mask] || reach_target[cmask];
        get_potion(r, l, new_mask, cmask);
        if (COMPILE) printf("leave_energy[%d] become %d\n", new_mask, leave_energy[new_mask]);
        unvisited[new_mask] = (unvisited[mask] | unvisited[cmask]);
        unvisited[new_mask] &= (~cmask);
        if (COMPILE) cout << "unvisited, new mask:" << bitset<sizeof(int)*8>(unvisited[new_mask]) << endl;
        res = max(res, trace_cave(new_mask));
      }
    }
  }
  mask_traced[mask] = res;
  if (COMPILE) printf("mask_traced(%d) set to true, with res: %d\n", mask, res);
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
    key_map.clear();
    pos_map.clear();
    leave_energy.clear();
    reach_target.clear();
    mask_traced.clear();
    unvisited.clear();
    memset(area, 0, sizeof(area));
    memset(area_array, 0, sizeof(area_array));
    memset(area_potion, 0, sizeof(area_potion));
    // setup key_map
    cnt_len = 0;
    key_map[mp(SR - 1, SC - 1)] = cnt_len++;
    pos_map[0] = mp(SR - 1, SC - 1);
    if (COMPILE) printf("key_map, (%d, %d): %d\n", SR - 1, SC - 1, cnt_len - 1);
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < M; k++) {
        if (is_trap(j, k)) {
          key_map[mp(j, k)] = cnt_len;
          pos_map[cnt_len++] = mp(j, k);
          if (COMPILE) printf("key_map, (%d, %d): %d\n", j, k, cnt_len - 1);
        }
      }
    }
    // previsit each point, get unvisited
    for (int j = 0; j < cnt_len; j++) {
      auto pos = pos_map[j];
      int mask = 1 << j;
      unvisited[mask] = 0;
      reach_target[mask] = 0;
      memset(traced, 0, sizeof(traced));
      trace_full(mask, pos.first, pos.second);
    }
    // area set
    trace_area();
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < M; k++) {
        if (COMPILE) {
          printf("area[%d][%d]: %d, area: %d, potion: %d\n", j, k, area_array[j][k], area[area_array[j][k]], area_potion[area_array[j][k]]);
        }
      }
    }
    // mask set to 1 to search
    int mask = 1;
    leave_energy[mask] = E;
    get_potion(SR - 1, SC - 1, mask, mask);
    int res = trace_cave(mask);
    if (COMPILE) printf ("res: %d\n", res);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
