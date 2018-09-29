#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int alphabet[26];

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  char name_array[100];
  char output_array[100];
  while (i < T) {
    int N = 0;
    scanf("%d\n", &N);
    int j = 0;
    int max_len = 0;
    while (j < N) {
      cin.getline(name_array, 100);
      memset(alphabet, 0, sizeof(alphabet));
      for (int k = 0; k < strlen(name_array); k++) {
        if ('A' <= name_array[k] && name_array[k] <= 'Z')
          alphabet[name_array[k] - 'A'] = 1;
      }
      int num = 0;
      for (int k = 0; k < 26; k++)
        if (alphabet[k] == 1)
          num++;
      if (max_len < num || (max_len == num && strcmp(name_array, output_array) < 0)) {
        max_len = num;
        strcpy(output_array, name_array);
      }
      j++;
    }
    i++;
    printf("Case #%d: %s\n", i, output_array);
  }
  
  return 0;
}
