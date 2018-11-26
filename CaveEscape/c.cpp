// In the name of God

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <deque>
#include <assert.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <math.h>
#include <bitset>
#include <iomanip>
#include <complex>

using namespace std;

#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> inline bool smin(T &a, const T &b)   { return a > b ? a = b : a;    }
template<typename T> inline bool smax(T &a, const T &b)   { return a < b ? a = b : a;    }

typedef long long LL;

const int N = (int) 105, M = 17, obs = -100000, mod = (int) 0;
int n, m, a[N][N], dist[M][N][N];
int px[M], py[M], c, sum[1 << M];
void add_point(int x, int y) {
	px[c] = x;
	py[c] = y;
	++c;
}
void dfs(int i, int j, int d[N][N]) {
	if (i < 0 || j < 0 || i >= n || j >= m) return;
	if (d[i][j] == 0) return;
	if (a[i][j] != obs)
		d[i][j] = 0;
	if (a[i][j] < 0) return;
	d[i][j] = 0;
	for (int a = -1; a <= 1; ++a)
		for (int b = -1; b <= 1; ++b)
			if (abs(a) + abs(b) == 1)
				dfs(i + a, j + b, d);
}
int par[N * N], over[N * N];
int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
void unite(int u, int v) {
	par[find(u)] = find(v);	
}
int main() {
	int tc;
    freopen("large.in", "r", stdin);
    freopen("large.out", "w", stdout);
	cin >> tc;
	for (int tt = 1; tt <= tc; ++tt) {
		c = 0;
		memset(over, 0, sizeof over);
		memset(sum, -1, sizeof sum);
		memset(dist, 0, sizeof dist);
		cout << "Case #" << tt << ": ";
		cin >> n >> m;
		int inite;
		cin >> inite;
		int sx, sy, tx, ty;
		cin >> sx >> sy >> tx >> ty;
		--sx, --sy, --tx, --ty;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				cin >> a[i][j];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				par[i * m + j] = i * m + j;	
			}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) if (a[i][j] >= 0) {
				for (int a = -1; a <= 1; ++a)
					for (int b = -1; b <= 1; ++b)
						if (abs(a) + abs(b) == 1) {
							int x = i + a, y = j + b;
							if (x >= 0 && x < n && y >= 0 && y < m) {
								if (::a[x][y] >= 0) unite(i * m + j, x * m + y);
							}
						}
			}
		vector<pair<int, int>> leads;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) if (a[i][j] >= 0) {
				if (par[i * m + j] == i * m + j)
					leads.push_back(mp(i, j));
				over[find(i * m + j)] += a[i][j];	
			}
		add_point(sx, sy);
		add_point(tx, ty);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (a[i][j] != obs && a[i][j] < 0)
					add_point(i, j);
		for (int p = 0; p < c; ++p) {
			memset(dist[p], 63, sizeof dist[p]);
			int tmp = a[px[p]][py[p]];
			a[px[p]][py[p]] = 0;
			dfs(px[p], py[p], dist[p]);
			a[px[p]][py[p]] = tmp;
		}
		memset(sum, -1, sizeof sum);
		sum[1] = inite;
		int res = -1;
		for (int mask = 1; mask < 1 << c; mask += 2) {

			if (sum[mask] >= 0 || mask == 1) {
				sum[mask] = inite;
				for (auto x : leads) {
					int can = 0;
					for (int j = 0; j < c; ++j)
						if ((mask >> j & 1) && dist[j][x.x][x.y] == 0)
							can = 1;
					if (can) {
						sum[mask] += over[x.x * m + x.y];
					}
				}
				for (int j = 0; j < c; ++j)
					if (mask >> j & 1)
						sum[mask] += a[px[j]][py[j]];
				for (int j = 0; j < c; ++j)
					if (~mask >> j & 1) {
						int can = 0;
						for (int i = 0; i < c; ++i)
							if (mask >> i & 1)
								if (dist[i][px[j]][py[j]] == 0)
									can = 1;
						if (can) {
							if (sum[mask] + a[px[j]][py[j]] >= 0) {
								sum[mask ^ (1 << j)] = max(sum[mask ^ (1 << j)], 0);	
							}
						}
					}
			}
			if (mask & 2) res = max(res, sum[mask]);
		}
		cout << res << endl;
	}
}

















