//lower_bound/upper_bound example
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector
#include <cstdio>
#include <map>

using namespace std;

struct Test {
  int a[5];
};

struct classcomp {
  bool operator() (const Test& x, const Test& y) const {
    return (x.a[0] < y.a[0]);
  }
}cc;

int main () {
  vector<Test> v;
  map<Test, int, classcomp> m;
  Test t;
  for (int i = 0; i < 5; i++)
    t.a[i] = i;
  m[t] = 1;
  v.push_back(t);
  Test tt;
  for (int i = 0; i < 5; i++)
    tt.a[i] = i - 1;
  m[tt] = 2;
  v.push_back(tt);
  printf("map 0: %d\n", m[t]);
  printf("map 1: %d\n", m[tt]);
  //int myints[26] = {10,20,30,30,20,10,10,20};
  //std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20
  sort (v.begin(), v.end(), cc);                // 10 10 10 20 20 20 30 30

  //std::vector<int>::iterator low,up;
  //low=std::lower_bound (v.begin(), v.end(), 20); //          ^
  //up= std::upper_bound (v.begin(), v.end(), 20); //                   ^
  for (int i = 0; i < v.size(); i++) {
    printf("rank: %d.\n", i);
    for (int j = 0; j < 5; j++)
      printf("item: %d.\n", v[i].a[j]);
  }

  return 0;
}
