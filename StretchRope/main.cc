#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 10001;
const long long INF = ~0ull >> 2;

long long dp[N];
int n, m, l;
int d[N], p, q;

int main() {
	int t, tt;
	scanf("%d", &t);
	for (tt = 1; tt <= t; tt++) {
		for (int i = 1; i < N; i++) dp[i] = INF;
		dp[0] = 0;
		scanf("%d%d%d", &n, &m, &l);
		for (int i = 0; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			p = q = 0;
			for (int j = a; l - j >= 0 && j < b; j++) {
				while (q > p && dp[d[q - 1]] >= dp[l - j]) q--;
				d[q++] = l - j;
			}
			for (int j = l; j >= 0; j--) {
				if (j - b >= 0) {
					while (q > p && dp[d[q - 1]] >= dp[j - b]) q--;
					d[q++] = j - b;
				}
				if (p < q) dp[j] = min(dp[j], dp[d[p]] + c);
				if (d[p] >= j - a) p++;
			}
		}
		if (dp[l] <= m) printf("Case #%d: %lld\n", tt, dp[l]);
		else printf("Case #%d: IMPOSSIBLE\n", tt);
	}
	return 0;
}
