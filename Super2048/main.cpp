#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void collide(int** array, int N, char* dir) {
  if (strcmp(dir, "right") == 0) {
    for (int i = 0; i < N; i++) { // i表示每一行
      int cur_rank = N - 1; // 当前要确定的方格
      for (int j = cur_rank - 1; 0 <= j; j--) {
        if (array[i][j] != 0) {
          if (array[i][cur_rank] == 0) {
            array[i][cur_rank] = array[i][j];
            array[i][j] = 0;
            continue;
          }
          if (array[i][j] == array[i][cur_rank]) {
            array[i][cur_rank--] <<= 1;
            array[i][j] = 0;
          } else {
            array[i][--cur_rank] = array[i][j];
            if (cur_rank != j)
              array[i][j] = 0;
          }
        }
      }
    }
  }
  if (strcmp(dir, "left") == 0) {
    for (int i = 0; i < N; i++) { // i表示每一行
      int cur_rank = 0; // 当前要确定的方格
      for (int j = 1; j < N; j++) {
        if (array[i][j] != 0) {
          if (array[i][cur_rank] == 0) {
            array[i][cur_rank] = array[i][j];
            array[i][j] = 0;
            continue;
          }
          if (array[i][j] == array[i][cur_rank]) {
            array[i][cur_rank++] <<= 1;
            array[i][j] = 0;
          } else {
            array[i][++cur_rank] = array[i][j];
            if (cur_rank != j)
              array[i][j] = 0;
          }
        }
      }
    }
  }
  if (strcmp(dir, "up") == 0) {
    for (int i = 0; i < N; i++) { // i表示每一列
      int cur_rank = 0; // 当前要确定的方格
      for (int j = 1; j < N; j++) {
        if (array[j][i] != 0) {
          if (array[cur_rank][i] == 0) {
            array[cur_rank][i] = array[j][i];
            array[j][i] = 0;
            continue;
          }
          if (array[j][i] == array[cur_rank][i]) {
            array[cur_rank++][i] <<= 1;
            array[j][i] = 0;
          } else {
            array[++cur_rank][i] = array[j][i];
            if (cur_rank != j)
              array[j][i] = 0;
          }
        }
      }
    }
  }
  if (strcmp(dir, "down") == 0) {
    for (int i = 0; i < N; i++) { // i表示每一列
      int cur_rank = N - 1; // 当前要确定的方格
      for (int j = cur_rank - 1; 0 <= j; j--) {
        if (array[j][i] != 0) {
          if (array[cur_rank][i] == 0) {
            array[cur_rank][i] = array[j][i];
            array[j][i] = 0;
            continue;
          }
          if (array[j][i] == array[cur_rank][i]) {
            array[cur_rank--][i] <<= 1;
            array[j][i] = 0;
          } else {
            array[--cur_rank][i] = array[j][i];
            if (cur_rank != j)
              array[j][i] = 0;
          }
        }
      }
    }
  }
}

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T = 0;
  scanf("%d", &T);
  int i = 0;
  while (i++ < T) {
    int N = 0;
    char dir[20];
    scanf("%d %s\n", &N, dir);
    int** super_array = new int*[N];
    for (int j = 0; j < N; j++) super_array[j] = new int[N];
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        scanf("%d", &super_array[j][k]);
    collide(super_array, N, dir);
    printf("Case #%d:\n", i);
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        printf("%d ", super_array[j][k]);
      }
      printf("\n");
    }
    for (int j = 0; j < N; j++) delete[] super_array[j];
    delete[] super_array;
  }
  return 0;
}
