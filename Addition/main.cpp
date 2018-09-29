#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

int main() {
  freopen("small.in", "r", stdin);
  freopen("small.out", "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  map<char*, int> add_map;
  int** add_array;
  while (i++ < T) {
    int N = 0;
    scanf("%d", &N);
    add_array = new int*[N];
    for (int k = 0; k < N; k++)
      add_array = new int[N];
    memset(add_array, 
    int j = 0, rank_map = 0;
    while (j++ < N) {
      char name_a[20], name_b[20];
      int value = 0;
      scanf("%s+%s=%d\n", name_a, name_b, &value);
      printf("add_map[a]:%d, [b]:%d\n", add_map[name_a], add_map[name_b]);
      if (!add_map[name_a]) add_map[name_a] = rank_map++;
      if (!add_map[name_b]) add_map[name_b] = rank_map++;
      add_array[add_map[name_a]][add_map[name_b]] = value;
    }
    printf("Case #%d:\n", i);
    int Q = 0;
    j = 0;
    while (j++ < Q) {
      char name_a[20], name_b[20];
      scanf("%s+%s\n", name_a, name_b);
      printf("%s+%s=%d\n", name_a, name_b, addition(name_a, name_b, add_map, add_array, N));
    }
    for (int k = 0; k < N; k++)
      delete[] add_array[k];
    delete[] add_array;
    add_map.clear();
  }
  return 0;
}
