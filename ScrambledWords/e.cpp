#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
using namespace std;

int main() {
    clock_t start;
    ifstream fin;
    fin.open("large.in");
    ofstream fout;
    fout.open("large.out");
    long long test;
    fin >> test;
    for (int i = 1; i <= test; i++) {
        vector<vector<vector<unordered_map<int, int>>>> f(26, vector<vector<unordered_map<int, int>>>(26, vector<unordered_map<int, int>>(1, unordered_map<int, int>())));
        unordered_set<int> used[26][26];
        unordered_set<int> len;
        vector<int> used_len;
        int l;
        fin >> l;
        while (l--) {
            string temp;
            fin >> temp;
            vector<int> g(26, 0);
            int t_l = temp.size();
            len.insert(t_l);
            for (int j = 0; j < t_l; j++) {
                g[temp[j] - 'a']++;
            }
            int s1 = temp[0] - 'a';
            int e1 = temp[t_l - 1] - 'a';
            used[s1][e1].insert(t_l);
            int cur = 0;
            for (int j = 0; j < 26; j++) {
                if (f[s1][e1][cur].find(g[j]) == f[s1][e1][cur].end()) {
                    unordered_map<int, int> temp;
                    f[s1][e1].emplace_back(temp);
                    f[s1][e1][cur][g[j]] = f[s1][e1].size() - 1;
                    cur = f[s1][e1].size() - 1;
                } else {
                    cur = f[s1][e1][cur][g[j]];
                }
            }
            f[s1][e1][cur][-1]++;
        }

        string s;
        char s1, s2;
        long long n, a, b, c, d;
        fin >> s1 >> s2 >> n >> a >> b >> c >> d;
        s += s1;
        s += s2;
        vector<vector<int>> sum(n, vector<int>(26, 0));
        sum[0][s1 - 'a']++;
        sum[1][s1 - 'a']++;
        sum[1][s2 - 'a']++;
        long long x1 = s1, x2 = s2;
        for (int j = 2; j < n; j++) {
            for (int k = 0; k < 26; k++) {
                sum[j][k] = sum[j - 1][k];
            }
            long long v1 = s1, v2 = s2;
            long long x = (x2 * a + x1 * b + c) % d;
            x1 = x2; x2 = x;
            sum[j][x % 26]++;
            s += char('a' + x % 26);
        }
        for (const auto& iter : len) {
            used_len.push_back(iter);
        }
        sort(used_len.begin(), used_len.end());
        int m = used_len.size(), ans = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (used_len[k] > j + 1) { break; }
                int s1 = s[j - used_len[k] + 1] - 'a';
                int e1 = s[j] - 'a';
                if (used[s1][e1].find(used_len[k]) == used[s1][e1].end()) { continue; }
                int cur = 0, pos = j - used_len[k] + 1;
                for (int l = 0; l < 26; l++) {
                    int val = sum[j][l];
                    if (pos - 1 >= 0) {
                        val -= sum[pos - 1][l];
                    }
                    if (f[s1][e1][cur].find(val) == f[s1][e1][cur].end()) {
                        cur = -1;
                        break;
                    }
                    cur = f[s1][e1][cur][val];
                }
                if (cur != -1 && f[s1][e1][cur][-1] > 0) {
                    ans += f[s1][e1][cur][-1];
                    f[s1][e1][cur][-1] = 0;
                }
            }
        }
        fout << "Case #" << i << ": " << ans << endl;
    }
    fin.close();
    fout.close();
    fout << "Total time:" << ((float) clock() - start) / CLOCKS_PER_SEC << endl;
    return 0;
}
