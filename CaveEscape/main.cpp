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

#define PR(x) cout << #x << ": " << x << endl;
#define mp make_pair
#define mt make_tuple
#define pb push_back

using namespace std;

#define LARGE 1000
#define COMPILE true
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, M, E, SR, SC, TR, TC;
int ini_array[LARGE][LARGE];
int trace[LARGE][LARGE];
map<pair<int, int>, int> untrack_map;

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

int trace_full(bool& rt, int r, int l, vector<pair<int, int>> &ca, decltype(untrack_map) &um) {
  if (is_target(r, l)) {
    if(COMPILE) printf("At (%d, %d), result reach.\n", r, l);
    reach_target = true;
  }
  for (auto& dir: direction(r, l)) {
    if (is_obstacle(dir.first, dir.second)) {
      continue;
    } else if (is_trap(dir.first, dir.second)) {
      if (is_traced(dir.first, dir.second)) {
        um.erase(mp(dir.first, dir.second));
      } else {
        tr.pb(mp(dir.first, dir.second));
        um[mt(ini_array[dir.first][dir.second], dir.first, dir.second)] = 1;
        trace[dir.first][dir.second] = 1;
        ca.pb(mp(dir.first, dir.second));
      }
    } else if (is_normal(dir.first, dir.second)) {
      trace[dir.first][dir.second] = 1;
      ca.pb(mp(dir.first, dir.second));
      trace_full(dir.first, dir.second, ca, tr, max_out, reach_target, um);
    } else if (is_potion(dir.first, dir.second)) {
      trace[dir.first][dir.second] = 1;
      ca.pb(mp(dir.first, dir.second));
      max_out += ini_array[dir.first][dir.second];
      trace_full(dir.first, dir.second, ca, tr, max_out, reach_target, um);
    }
  }
}

int trace_parrell(bool& rt, decltype(untrack_map) um) {
  decltype(untrack_map) need_track;
  for (auto& m: um) {
    if (!need_track[m.first]) continue;
    // 3. use this route & track the leave
    int cr = trace_cave(rt, current_energy + delta + ini_array[r][l], num);
    if (is_isolate) need_track[m.first] = false;
  }
  if (!finish) trace_parrell(rt, um);
}

int trace_cave(bool& reach_target, pair<int, int> cp, int current_energy, decltype(untrack_map) um) {
  int max_out = -1;
  int rt_max = -1;
  // 1. get item
  int e = current_energy, r = cp.first, l = cp.second;
  // 2. ini ca
  vector<pair<int, int>> ca;
  decltype(untrck_map) num(um);
  bool rt = reach_target;
  int delta = trace_full(rt, r, l, ca, num);
  int cr = trace_parrell(rt, num);
  if (rt && max_out < cr) { reach_target = true; max_out = cr; }
  return max_out;
  }
  // 4. clean ca
  for (auto& t: ca) {
    int r = t.first, l = t.second;
    trace[r][l] = -1;
  }
  return max_out;
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
    memset(trace, -1, sizeof(trace));
    auto cp = mp(SR - 1, SC - 1);
    untrack_map.clear();
    untrack_map[cp] = 1;
    bool reach_target = false;
    int current_energy = E;
    int res = trace_cave(reach_target, cp, current_energy, untrack_map);
    if (!reach_target) res = -1;
    if (COMPILE) printf ("res: %d\n", res);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
