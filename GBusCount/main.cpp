#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

string get_file_name(char* s) {
  int len_s = strlen(s);
  string res = "";
  for (int i = 0; i < len_s; i++) {
    if (s[i] == '.') break;
    res += s[i];
  }
  return res;
}

int main(int argc, char** argv) {
  if (argc <= 1) { printf("Please give file parameters;"); return -1;}
  string ifn = get_file_name(argv[1]);
  printf("%s", (ifn + ".out").c_str());
  freopen((ifn + ".in").c_str(), "r", stdin);
  freopen((ifn + ".out").c_str(), "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  int bus_start[1000];
  int bus_end[1000];
  while (i++ < T) {
    int N = 0;
    scanf("%d\n", &N);
    int j = 0;
    while (j < N) {
      scanf("%d", &bus_start[j]);
      scanf("%d", &bus_end[j]);
      j++;
    }
    int P = 0;
    scanf("%d\n", &P);
    int k = 0;
    printf("Case #%d:", i);
    int num;
    while (k < P) {
      scanf("%d\n", &num);
      int cnt = 0;
      for (int m = 0; m < N; m++) {
        if (bus_start[m] <= num && num <= bus_end[m])
          cnt++;
      }
      printf(" %d", cnt);
      k++;
    }
    printf("\n");
  }
  
  return 0;
}
