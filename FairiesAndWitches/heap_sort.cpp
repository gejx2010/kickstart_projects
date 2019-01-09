#include <iostream>
#include <cstdio>

using namespace std;

void sweap_down(int* a, int num, int rank) {
  do {
    int left = (rank * 2 + 1 < num) ? rank * 2 + 1 : num;
    int right = (rank * 2 + 2 < num) ? rank * 2 + 2 : num;
    int max = a[rank], r = rank;
    if (num <= left) break;
    else if (max < a[left]) { max = a[left], r = left; }
    if (right < num && max < a[right]) { max = a[right], r = right; }
    if (rank == r) break;
    a[r] = a[rank];
    a[rank] = max;
    rank = r;
  } while (rank * 2 + 1 < num);
}

void build_heap(int* a, int num) {
  for (int i = num / 2 - 1; 0 <= i; i--) {
    sweap_down(a, num, i);
  }
}

int percolate(int* a, int num) {
  if (num == 1) return a[0];
  // sweap the first num down to last
  int m = a[0];
  a[0] = a[num - 1];
  a[num - 1] = m;
  // sweap from the top to last
  sweap_down(a, num - 1, 0);
  return a[0];
}

int kth_element(int* a, int num, int rank) {
  // tail O(n) to build sort
  build_heap(a, num);
  // Take k round percolate
  int cur_num = num, res = a[0];
  for (int i = 0; i < rank; i++) {
    res = percolate(a, cur_num--);
  }
  return res;
}

void heap_sort(int* a, int num) {
  // first set up the heap first, use time O(n)
  build_heap(a, num);
  // Then percolate the heap, each item use time O(logn), total O(nlogn)
  for (int i = 0, cur_num = num; i < num; i++, cur_num--)
    percolate(a, cur_num);
}

int main() {
  int* a = new int[20];
  int N = 0;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &a[i]);
  heap_sort(a, N);
  printf("After heap sort.\n");
  for (int i = 0; i < N; i++) printf("%d ", a[i]);
  printf("\n");
  return 0;
}
