#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define SEVEN_NUM 7
#define TEN_NUM 10

char seven_num_array[10][SEVEN_NUM + 1] = {
  {"1111110"},
  {"0110000"},
  {"1101101"},
  {"1111001"},
  {"0110011"},
  {"1011011"},
  {"1011111"},
  {"1110000"},
  {"1111111"},
  {"1111011"}
};
 
enum STATUS {
  NOT_SURE = 0,
  BROKEN,
  NORMAL
};

bool canbe(char* st, int n, STATUS* broken) {
  for (int i = 0; i < SEVEN_NUM; i++) {
    if (st[i] == '1' && seven_num_array[n][i] == '0') return false;
    if (st[i] == '1' && broken[i] == BROKEN) return false;
    if (st[i] == '0' && seven_num_array[n][i] == '1' && broken[i] == NORMAL) return false;
    if (seven_num_array[n][i] == '1' && st[i] == '0') {
        if (broken[i] == NORMAL) return false;
        else broken[i] = BROKEN;
    }
    if (st[i] == '1' && seven_num_array[n][i] == '1') {
        if (broken[i] == BROKEN) return false;
        else broken[i] = NORMAL;
    }
  }
  return true;
}

char* predict(char** state, int N) {
  //bool isAllZero = true;
  //bool isCyclic = true;
  //char cyclic[TEN_NUM][SEVEN_NUM + 1];
  //// determine if is all zero
  //for (int i = 0; i < N; i++) {
  //  if (strcmp(state[i], "0000000") != 0) {
  //    isAllZero = false;
  //  }
  //}
  //// determine if is cyclic
  //if (TEN_NUM <= N) {
  //  for (int i = 0; i < N; i++) {
  //    if (N < TEN_NUM) strcpy(cyclic[i], state[i]);
  //    else {
  //      if (strcmp(cyclic[i % 10], state[i]) != 0) {
  //        isCyclic = false;
  //        break;
  //      }
  //    }
  //  }
  //  if (isCyclic) {
  //    return cyclic[N % 10];
  //  } else {
  //    return "ERROR!";
  //  }
  //}
  //if (isAllZero && 3 < N) return "0000000";
  STATUS broken[SEVEN_NUM];
  STATUS out_broken[TEN_NUM][SEVEN_NUM];
  char out_str[TEN_NUM][SEVEN_NUM + 1];
  memset(out_broken, 0, sizeof(out_broken));
  int cnt_prop = 0;
  int cur_num;
  int out_num;
  for (int i = 0; i < TEN_NUM; i++) {
    cur_num = i;
    int j = 0;
    memset(broken, 0, sizeof(broken));
    for (; j < N; j++) {
      if (!canbe(state[j], cur_num, broken))  
        break;
      cur_num = (cur_num == 0) ? 9 : cur_num - 1;
    }
    if (j == N) {
      out_num = cur_num;
      for (int k = 0; k < SEVEN_NUM; k++) {
        out_broken[cnt_prop][k] = broken[k];
      }
      strcpy(out_str[i], seven_num_array[cur_num]);
      for (int k = 0; k < SEVEN_NUM; k++) {
        if (out_str[i][k] == '1' && broken[k] == BROKEN) {
          out_str[i][k] = '0';
        }
        if (out_str[i][k] == '1' && broken[k] == NOT_SURE) {
          strcpy(out_str[i], "ONE");
          break;
        }
      }
      cnt_prop++;
      //printf("cur_num:%d\n",cur_num);
    } else {
      strcpy(out_str[i], "ZERO");
    }
  }
  //printf("cnt_prop:%d\n", cnt_prop);
  if (cnt_prop == 0) return "ERROR!";
  else {
    char* bef = new char[SEVEN_NUM + 1];
    strcpy(bef, "BEGIN");
    for (int i = 0; i < TEN_NUM; i++) {
      if (strcmp(out_str[i], "ONE") == 0) return "ERROR!";
      if (strcmp(out_str[i], "ZERO") != 0) {
        if (strcmp(bef, "BEGIN") == 0) {
          strcpy(bef, out_str[i]);
        } else if (strcmp(bef, out_str[i]) != 0) {
          return "ERROR!";
        }
      }
    }
    if (strcmp(bef, "BEGIN") != 0) {
      return bef;
    }
  }
}

int main() {
  freopen("large.in", "r", stdin);
  freopen("large.out", "w", stdout);
  int T;
  scanf("%d\n", &T);
  int i = 0;
  char** state;
  while (i++ < T) {
    int N;
    scanf("%d", &N);
    state = new char*[N];
    int j = 0;
    for (; j < N; j++) state[j] = new char[SEVEN_NUM + 1];
    j = 0;
    while (j++ < N) {
      scanf("%s", state[j - 1]);
    }
    char* out_str = predict(state, N);
    printf("Case #%d: %s\n", i, out_str);
    for (; j < N; j++) delete[] state[j];
    delete state;
  }
  return 0;
}
