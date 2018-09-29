#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  if (argc <= 1) { printf("Please give file parameters;"); return -1;}
  string ifn = string(strtok(argv[1], "."));
  printf("%s\n", (ifn + ".out").c_str());
  freopen((ifn + ".in").c_str(), "r", stdin);
  freopen((ifn + ".out").c_str(), "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  char* start = new char[100], *end = new char[100];
  vector< pair<char*, char*> > flight;
  map<string, int> cnt_first, cnt_next;
  while (i++ < T) {
    int N = 0;
    scanf("%d\n", &N);
    cnt_first.clear(), cnt_next.clear(), flight.clear();
    int j = 0;
    while (j++ < N) {
      scanf("%s\n", start);
      scanf("%s\n", end);
      flight.push_back(make_pair(start, end));
      cnt_first[start] = j - 1;
      cnt_next[end] = j - 1;
      start = new char[100], end = new char[100];
    }
    map<string, int>::iterator iter;
    for (iter = cnt_first.begin(); iter != cnt_first.end(); iter++) {
      if (cnt_next.count(iter->first) == 0) {
        strcpy(start, iter->first.c_str());
      }
    }
    printf("Case #%d:", i); 
    int k = 0;
    char* f = start;
    while (k++ < N) {
      printf(" %s-%s", f, flight[cnt_first[f]].second);
      f = flight[cnt_first[f]].second;
    }
    printf("\n");
  }
  return 0;
}
