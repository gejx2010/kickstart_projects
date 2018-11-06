#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <random>
using namespace std;
#define db(x) cerr << #x << "=" << x << endl
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << endl
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
char str[100005], S[1000005];
ll X[1000005];
vector<string> words[100005];
ull val[35], firv, lasv;
int main() {
    freopen("large.in", "r", stdin);
    freopen("large.out", "w", stdout); 
    clock_t st = clock();
	mt19937_64 rng(24);
	for (int i = 0; i < 26; ++i) val[i] = rng();
	firv = rng();
	lasv = rng();
    db(firv);
    db(lasv);
    for (int i = 0; i < 26; ++i) cerr << val[i] << endl;
	int TC;
	scanf("%d", &TC);
	for (int cn = 1; cn <= TC; ++cn) {
		int L;
		scanf("%d", &L);
		for (int i = 1; i <= 100000; ++i) words[i].clear();
		for (int i = 0; i < L; ++i) {
			scanf("%s", str);
			words[strlen(str)].push_back(str);
		}
		int N;
		ll A, B, C, D;
		scanf(" %c %c%d%lld%lld%lld%lld", &S[0], &S[1], &N, &A, &B, &C, &D);
		X[0] = S[0];
		X[1] = S[1];
		for (int i = 2; i < N; ++i) {
			X[i] = (A * X[i - 1] + B * X[i - 2] + C) % D;
			S[i] = 97 + (X[i] % 26);
		}
		S[N] = '\0';
		int ans = 0;
		for (int len = 2; len <= 100000; ++len) {
			if (words[len].empty()) continue;
			if (len > N) break;
			unordered_set<ull> H;
			ull h = firv * (S[0] - 'a') + lasv * (S[len - 1] - 'a');
			for (int i = 1; i + 1 < len; ++i) {
				h += val[S[i] - 'a'];
			}
			H.insert(h);
			for (int i = len; i < N; ++i) {
				h -= firv * (S[i - len] - 'a');
				if (len > 2) h -= val[S[i - len + 1] - 'a'];
				h -= lasv * (S[i - 1] - 'a');
				if (len > 2) h += val[S[i - 1] - 'a'];
				h += lasv * (S[i] - 'a');
				h += firv * (S[i - len + 1] - 'a');
				H.insert(h);
			}
			for (string s : words[len]) {
				ull h = firv * (s[0] - 'a') + lasv * (s[len - 1] - 'a');
				for (int i = 1; i + 1 < len; ++i) {
					h += val[s[i] - 'a'];
				}
				if (H.count(h)) {
					++ans;
				}
			}
		}
		printf("Case #%d: %d\n", cn, ans);
		cerr << "test " << cn << " done\n";
	}
    printf ("Take total time: %f seconds.\n", ((float)(clock() - st)) / CLOCKS_PER_SEC);
}

