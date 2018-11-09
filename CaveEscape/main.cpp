#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <stack>

#define PR(x) cout << #x << ": " << x << endl;
#define mp(x,y) make_pair(x, y)

using namespace std;

#define LARGE 1000
#define COMPILE false
#define TESTTIME false

// define initial parameters here
int T = 0;
int N, M, E, SR, SC, TR, TC;
int ini_array[LARGE][LARGE];
int trace[LARGE][LARGE];
vector<int> result_energy;
stack< pair< pair<int, int>, int > > trap_layer;

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
  return (r == TR && l == TC);
}

bool is_traced(int r, int l) {
  return (trace[r][l] != 0);
}

vector< pair<int, int> > direction(int r, int l) {
  vector< pair<int, int> > res;
  if (0 < r) res.push_back(make_pair(r - 1, l));
  if (0 < l) res.push_back(make_pair(r, l - 1));
  if (r < N - 1) res.push_back(make_pair(r + 1, l));
  if (l < M - 1) res.push_back(make_pair(r, l + 1));
  return res;
}

void trace_full(int r, int l, int e) {
  for (auto& dir: direction(r, l)) {
    if (is_obstacle(dir.first, dir.second)) {
      continue;
    } else if (is_potion(dir.first, dir.second)) {
      trace[dir.first][dir.second] = 1;
      trace_full(dir.first, dir.second, e + ini_array[dir.first][dir.second]);
      trace[dir.first][dir.second] = 0;
    } else if (is_trap(dir.first, dir.second)) {
      if (!is_traced(dir.first, dir.second) && 0 < e + ini_array[dir.first][dir.second])
        trap_layer.push(mp(mp(dir.first, dir.second), e + ini_array[dir.first][dir.second]));
    } else if (is_normal(dir.first, dir.second) && !is_traced(dir.first, dir.second)) {
      trace[dir.first][dir.second] = 1;
      trace_full(dir.first, dir.second, e);
    }
  }
}

void trace_each_trap(int r, int l, int e, vector<pair<int, int>> ca) {
  trace[r][e] = 1;
  trace_full(r, l, e, ca);
  while (!trap_layer.empty()) {
    
  }
}

void trace_cave() {
  if (trap_layer.empty()) return;
  int r = trap_layer.top().first.first;
  int l = trap_layer.top().first.second;
  int e = trap_layer.top().second;
  PR(r);
  PR(l);
  PR(e);
  vector<pair<int, int>> ca;
  trace_each_trap(r, l, e, ca);
  for (int i = 0; i < ca.size(); i++) {
    trace[ca[i].first][ca[i].second] = 0;
  }
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
    for (int j = 0; j < N; j++) 
      for (int k = 0; k < M; k++) 
        scanf("%d", &ini_array[j][k]);
    memset(trace, 0, sizeof(trace));
    result_energy.clear();
    trace[SR][SC] = 1;
    trap_layer.push(mp(mp(SR, SC), E));
    trace_cave();
    int res = -1;
    printf ("res: %d\n", res);
    if (!result_energy.empty()) res = *max_element(result_energy.begin(), result_energy.end());
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}
