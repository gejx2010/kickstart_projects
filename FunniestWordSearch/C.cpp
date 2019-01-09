#include <stdio.h>
#include <string.h>
#include <algorithm>

const int MAXN = 105;

int R, C, W;

char a[MAXN][MAXN];

int next[10005][26];
int weight[10005];
int n_nodes;

void insert(char *s, int len) {
	int id = 1;
	for (int i = 0; i < len; i++) {
		int t = s[i] - 'A';
		if (!next[id][t]) {
			next[id][t] = ++n_nodes;
		}
		id = next[id][t];
	}
	weight[id] += len;
}

long long sum_d[MAXN][MAXN][MAXN];
long long sum_r[MAXN][MAXN][MAXN];

long long sumint_d[MAXN][MAXN][MAXN];
long long sumint_r[MAXN][MAXN][MAXN];

void solve() {
	scanf("%d%d%d", &R, &C, &W);
	for (int i = 1; i <= R; i++) {
		scanf("%s", a[i] + 1);
	}
	memset(next, 0, sizeof(next));
	memset(weight, 0, sizeof(weight));
	n_nodes = 1;
	for (int i = 1; i <= W; i++) {
		char buf[5005];
		scanf("%s", buf);
		int len = strlen(buf);
		insert(buf, len);
		std::reverse(buf, buf + len);
		insert(buf, len);
	}
	
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int id;
			
			id = 1;
			sum_d[i][j][i - 1] = 0;
			for (int k = i; k <= R; k++) {
				id = next[id][(int) a[k][j] - 'A'];
				sum_d[i][j][k] = sum_d[i][j][k - 1] + weight[id];
			}
			
			id = 1;
			sum_r[i][j][j - 1] = 0;
			for (int k = j; k <= C; k++) {
				id = next[id][(int) a[i][k] - 'A'];
				sum_r[i][j][k] = sum_r[i][j][k - 1] + weight[id];
			}
		}
	}
	
	for (int c = 1; c <= C; c++) {
		for (int i = 1; i <= R; i++) {
			for (int j = i; j <= R; j++) {
				long long tmp = 0;
				for (int k = i; k <= j; k++) {
					tmp += sum_d[k][c][j];
				}
				sumint_d[c][i][j] = sumint_d[c - 1][i][j] + tmp;
			}
		}
	}
	
	for (int r = 1; r <= R; r++) {
		for (int i = 1; i <= C; i++) {
			for (int j = 1; j <= C; j++) {
				long long tmp = 0;
				for (int k = i; k <= j; k++) {
					tmp += sum_r[r][k][j];
				}
				sumint_r[r][i][j] = sumint_r[r - 1][i][j] + tmp;
			}
		}
	}
	
	long long max1 = 0;
	int max2 = 1;
	int cnt = 0;
	
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			for (int x = i; x <= R; x++) {
				for (int y = j; y <= C; y++) {
					int w = x - i + 1;
					int h = y - j + 1;
					long long tmp1 = sumint_d[y][i][x] - sumint_d[j - 1][i][x];
					tmp1 += sumint_r[x][j][y] - sumint_r[i - 1][j][y];
					int tmp2 = w + h;
					if (tmp1 * max2 > tmp2 * max1) {
						max1 = tmp1;
						max2 = tmp2;
						cnt = 1;
					} else if (tmp1 * max2 == tmp2 * max1) {
						++cnt;
					}
				}
			}
		}
	}
	
	int g = std::__gcd(max1, 1LL * max2);
	printf("%lld/%d %d\n", max1 / g, max2 / g, cnt);
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out.bcp", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		printf("Case #%d: ", i);
        clock_t st = clock();
		solve();
        clock_t ed = clock();
        //printf("case %d takes time: %f seconds\n", i, ((float) ed - st) / CLOCKS_PER_SEC);
	}
}
