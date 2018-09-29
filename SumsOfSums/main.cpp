#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>

using namespace std;

#define LARGE 200001
#define COMPILE false
#define TESTTIME false
#define SUBCOMPILE false

int ini_array[LARGE], sum_array[LARGE];
long long ss_array[LARGE];
int left_array[LARGE], right_array[LARGE];
int left_bound[LARGE], right_bound[LARGE];
long long ini_rank[LARGE];
pair<int, int> merge_bef_array[LARGE * 200];

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

/*
 * search with [0, end) where end is appointed by line_number
 */ 
int local_search(int number, int num, int line_number, bool strict) {
  if (COMPILE) printf("Begin local_search, number: %d, num: %d, line_number: %d.\n", number, num, line_number);
  int start = line_number, end = num;
  int mid = (start + end) / 2;
  int debuff = 0;
  if (0 < line_number) debuff = sum_array[line_number - 1];
  while (start < end) {
    if (sum_array[mid] - debuff < number) start = mid + 1;
    else if (number < sum_array[mid] - debuff) end = mid;
    else if (strict) return mid + 1 - line_number;
    else return mid - line_number;
    mid = (start + end) / 2;
  }
  int res = mid - line_number;
  if (COMPILE) printf("After local_search, return answer: %d.\n", res);
  return res;
}

/*
 * compute the rank of each number
 */
long long get_rank_with_number(int number, int num, int line_number=0) {
  if (COMPILE) printf("Begin get_rank_with_number, number: %d, num: %d, line_number: %d.\n", number, num, line_number);
  long long ini = 0;
  for (int i = 0; i < num; i++) {
    if (i < line_number) ini += local_search(number, num, i, true);
    else ini += local_search(number, num, i, false);
  }
  if (COMPILE) printf("After get_rank_with_number, return answer: %d.\n", ini);
  return ini + 1;
}

long long try_get_ini_rank_with_number(int id, int num) {
  if (ini_rank[id] != 0) return ini_rank[id];
  return get_rank_with_number(sum_array[id], num, 0);
}

/*
 *
 */
int rank_search(long long number, int num) {
  int start = 0, end = num;
  while (start < end) {
    int mid = (start + end) / 2;
    long long cur_rank = try_get_ini_rank_with_number(mid, num);
    if (cur_rank < number) start = mid + 1;
    else if (number < cur_rank) end = mid;
    else return mid;
  }
  return start - 1;
}

void get_bound_with_number(int* a, int number, int num, int line_number=0) {
  for (int i = 0; i < num; i++) {
    if (i < line_number) a[i] = local_search(number, num, i, true);
    else a[i] = local_search(number, num, i, false);
  }
}

//void merge_array_each_line(int cur_line, int num, int rank) {
//  merge_aft_array.clear();
//  int i = 0, j = left_bound[cur_line];
//  int ni = merge_bef_array.size(), nj = right_bound[cur_line];
//  if (nj <= j) return;
//  int bias = 0;
//  if (0 < cur_line) bias = sum_array[cur_line - 1];
//  if (ni <= 0) {
//    while (j < nj) {
//      merge_bef_array.push_back(make_pair(sum_array[cur_line + (j++)] - bias, cur_line));
//    }
//    return;
//  }
//  while (i < ni && j < nj) {
//    while (i < ni && merge_bef_array[i].first <= sum_array[cur_line + j] - bias) 
//      merge_aft_array.push_back(merge_bef_array[i++]);
//    if (i == ni) {
//      while (j < nj) 
//        merge_aft_array.push_back(make_pair(sum_array[cur_line + (j++)] - bias, cur_line));
//      break;
//    }
//    while (j < nj && sum_array[cur_line + j] - bias < merge_bef_array[i].first) 
//      merge_aft_array.push_back(make_pair(sum_array[cur_line + (j++)] - bias, cur_line));
//    if (j == nj) {
//      while (i < ni) 
//        merge_aft_array.push_back(merge_bef_array[i++]);
//      break;
//    }
//  }
//  // copy from aft to bef
//  merge_bef_array.clear();
//  for (int i = 0; i < merge_aft_array.size(); i++)
//    merge_bef_array.push_back(merge_aft_array[i]);
//}

int locate(int start, int end) {
  pair<int, int> m = merge_bef_array[start];
  int i = start,  j = end - 1;
  while (i != j) {
    while (i < j && m.first <= merge_bef_array[j].first) j--;
    if (i < j) merge_bef_array[i++] = merge_bef_array[j]; 
    while (i < j && merge_bef_array[i].first <= m.first) i++;
    if (i < j) merge_bef_array[j--] = merge_bef_array[i];
  }
  merge_bef_array[i] = m;
  return i;
}

void find_kth(int rank, int start, int end) {
  // get the position of the first number
  int res = locate(start, end);
  if (res == rank) return;
  if (rank < res) return find_kth(rank, start, res);
  return find_kth(rank, res + 1, end);
}

void merge_array(long long rank, int num, int &res_num, int &line_num) {
  // merge each line with bef array
  int cur_rank = 0, bias = 0;
  for (int i = 0; i < num; i++) { 
    if (0 < i) bias = sum_array[i - 1];
    for (int j = left_bound[i]; j < right_bound[i]; j++)
      merge_bef_array[cur_rank++] = make_pair(sum_array[i + j] - bias, i);
  }
  if (COMPILE)
    for (int i = 0; i < cur_rank; i++)
      printf("%d: (%d, %d)\n", i, merge_bef_array[i].first, merge_bef_array[i].second);
  //find_kth(rank, 0, cur_rank);
  nth_element(merge_bef_array, merge_bef_array + rank, merge_bef_array + cur_rank, less<pair<int, int> >());
  if (COMPILE)
    for (int i = 0; i < cur_rank; i++)
      printf("%d: (%d, %d)\n", i, merge_bef_array[i].first, merge_bef_array[i].second);
  res_num = merge_bef_array[rank].first;
  line_num = merge_bef_array[rank].second;
  return;
}

/*
 * compute the bound of array and write it into left_array
 */
void get_bound_with_rank(int* input_array, long long rank, int num, int &valid) {
  clock_t st = clock();
  // get the rank of first line
  int cur_rank = rank_search(rank, num);
  if (SUBCOMPILE) {
    printf("@get_bound_with_rank, input_rank: %lld, cur_rank: %d.\n", rank, cur_rank);
  }
  int start = cur_rank;
  long long base_rank = 1;
  if (0 <= start) base_rank = try_get_ini_rank_with_number(cur_rank, num);
  // write bound of each number
  if (start < 0) {
    memset(left_bound, 0, sizeof(left_bound));
    get_bound_with_number(right_bound, sum_array[0], num);
  } else if (start < num - 1) {
    get_bound_with_number(left_bound, sum_array[start], num);
    get_bound_with_number(right_bound, sum_array[start + 1], num);
  } else {
    for (int i = 0; i < num; i++) {
      left_bound[i] = (i == 0) ? num - 1 : num - i;
      right_bound[i] = num - i;
    }
  }
  if (COMPILE) 
    printf_array(left_bound, num, "@get_bound_with_rank:left_bound", "int");
  if (COMPILE) 
    printf_array(right_bound, num, "@get_bound_with_rank:right_bound", "int");
  clock_t bound_time = clock();
  if (TESTTIME) printf("Get the bound takes time %f seconds.\n", ((float)(bound_time - st)) / CLOCKS_PER_SEC);
  // merge array and get the k-th
  int line_number = 0, res_num = 0;
  if (COMPILE) 
    printf("@get_bound_with_rank, Leave rank: %d.\n", rank - base_rank);
  merge_array(rank - base_rank, num, res_num, line_number);
  if (SUBCOMPILE) 
    printf("@get_bound_with_rank, res_num: %d, line_number: %d.\n", res_num, line_number);
  valid = line_number;
  clock_t merge_time = clock();
  if (TESTTIME) printf("Merge array takes time %f seconds.\n", ((float)(merge_time - bound_time)) / CLOCKS_PER_SEC);
  // again get the definite bound
  get_bound_with_number(input_array, res_num, num, line_number);
  clock_t def_time = clock();
  if (TESTTIME) printf("Define the bound takes time %f seconds.\n", ((float)(def_time - merge_time)) / CLOCKS_PER_SEC);
}

/*
 * compute the rank'th line with [left, right)
 */ 
long long compute_sum_with_rank(int left, int right, int rank, int right_valid) {
  if (SUBCOMPILE) printf("@compute_sum_with_rank, left: %d, right %d, rank: %d, right_valid: %d.\n", left, right, rank, right_valid);
  if (right < left) return 0;
  long long bias = 0;
  if (0 < rank) bias = sum_array[rank - 1];
  if (SUBCOMPILE) printf("@compute_sum_with_rank, bias: %lld", bias);
  long long end = 0;
  if (0 < left + rank) end = ss_array[left + rank - 1];
  if (SUBCOMPILE) printf("@compute_sum_with_rank, end: %lld", end);
  long long start = 0;
  if (0 < right + rank) start = ss_array[right + rank - 1];
  if (SUBCOMPILE) printf("@compute_sum_with_rank, start: %lld", start);
  long long res = start - end - (right - left) * bias;
  if (SUBCOMPILE) printf("@compute_sum_with_rank, res_1: %lld", res);
  if (rank == right_valid) res += (long long)sum_array[right + rank] - bias;
  if (SUBCOMPILE) printf("@compute_sum_with_rank, res_2: %lld", res);
  return res;
  //if (rank == 0) {
  //  if (rank != right_valid)
  //    if (0 < left) return ss_array[right - 1] - ss_array[left - 1];
  //    else return ss_array[right - 1];
  //  else 
  //    if (0 < left) return ss_array[right] - ss_array[left - 1];
  //    else return ss_array[right];
  //} else {
  //  if (rank != right_valid)
  //    return ss_array[right + rank - 1] - ss_array[left + rank - 1] - ((long long)(right - left)) * sum_array[rank - 1];
  //  else
  //    return ss_array[right + rank] - ss_array[left + rank - 1] - ((long long)(right - left + 1)) * sum_array[rank - 1];
  //}
}

long long compute_sum(int num, int left_valid, int right_valid) {
  // here, right_valid < left_valid is asserted
  clock_t st = clock();
  long long sum = 0;
  for (int i = 0; i < num; i++) {
    sum += compute_sum_with_rank(left_array[i], right_array[i], i, right_valid);
    if (COMPILE) printf("@compute_sum, final sum: %d.\n", sum);
  }
  if (TESTTIME) printf("Compute sum takes time %f seconds.\n", ((float)(clock() - st)) / CLOCKS_PER_SEC);
  return sum;
}

long long process(long long left, long long right, int num) {
  // first get left and right array, write in left_array and the valid number into valid_num
  int valid_num_left = 0, valid_num_right = 0;
  get_bound_with_rank(left_array, left, num, valid_num_left);
  if (COMPILE) 
    printf_array(left_array, num, "@process_left_array", "int");
  get_bound_with_rank(right_array, right, num, valid_num_right);
  if (COMPILE) 
    printf_array(right_array, num, "@process_right_array", "int");
  // compute the sum
  return compute_sum(num, valid_num_left, valid_num_right);
}

int main(int argc, char** argv) {
  char* def_ifn = "large.in";
  char* def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn, "r", stdin);
  freopen(def_ofn, "w", stdout);
  int T = 0;
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  int i = 0, N = 0, Q = 0;
  while (i++ < T) {
    clock_t st = clock();
    if (TESTTIME) printf("With Case %d.\n", i);
    scanf("%d %d", &N, &Q);
    if (COMPILE) printf("Get (N, Q) as (%d, %d).\n", N, Q);
    // read in array and ini sum and sum_sum
    int j = 0, sum_ini = 0;
    long long ss_ini = 0;
    while (j < N) {
      scanf("%d", &ini_array[j]);
      sum_ini += ini_array[j];
      sum_array[j] = sum_ini;
      ss_ini += sum_ini;
      ss_array[j] = ss_ini;
      j++;
    }
    memset(ini_rank, 0, sizeof(ini_rank));
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, N, "ini_array", "int");
    if (COMPILE) printf_array(sum_array, N, "sum_array", "int"); 
    // read in Q test and process
    printf("Case #%d:\n", i);
    j = 0;
    long long li = 0, ri = 0;
    while (j < Q) {
      clock_t bt = clock();
      if (TESTTIME) printf("Begin process the %d problem.\n", j + 1);
      scanf("%lld %lld", &li, &ri);
      if (COMPILE) 
        printf("Get left, right as (%d, %d).\n", li, ri);
      printf("%lld\n", process(li, ri, N));
      j++;
      clock_t et = clock();
      if (TESTTIME) printf("Process takes time: %f seconds\n", ((float)(et - bt)) / CLOCKS_PER_SEC);
    }
  }
  return 0;
}
