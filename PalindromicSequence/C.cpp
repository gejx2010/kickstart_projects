#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }

void io(string s = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (sz(s)) {
        setIn(s+".in");
        setOut(s+".out");
    }
}

int L;
ll N, K;

ll getPal(int len) {
    ll res = 1; F0R(i,(len+1)/2) res *= L;
    return res;
}

string bad(string S, int num) {
    string t = S.substr(0,(num+1)/2);
    string res = t; reverse(all(t)); if (num&1) t.erase(t.begin()); res += t; 
    return res;
}

ll enumerate(string s) {
    ll cpo = 1, ans = 0;
    F0Rd(i,sz(s)) {
        ans += cpo*(s[i]-'a');
        cpo *= L;
    }
    return ans;
}

ll GET(int i, string S) { // less than S 
    int num = (i+1)/2;
    while (sz(S) < num) S += 'a';
    ll t = enumerate(S.substr(0,num));
    return t+(bad(S,i) < S);
}

ll get(ll n, string S) {
    ll tmp = 0;
    F0R(i,n+1) tmp += GET(i,S);
    return tmp;
}

ll tri(ll n) { // len <= n
    string s = ""; 
    while (sz(s) < n) {
        int nex = L-1;
        F0R(i,L) {
            string S = s+char('a'+i);
            if (get(n,S) >= K) {
                nex = i-1;
                break;
            }
        }
        if (nex == -1) break;
        s += char('a'+nex);
    }
    return sz(s);
}

void solve() {
    cin >> L >> N >> K;
    if (K <= N) {
        cout << K;
        return;
    }
    if (L == 1) {
        cout << 0;
        return;
    }
    K -= N;
    for (ll i = N/2; i >= 0; --i) {
        ll num = 0;
        F0R(len,N-2*i+1) num += getPal(len)-1;
        if (num >= K) {
            K += N-2*i+1;
            cout << 2*i+tri(N-2*i);
            return;
        }
        // how many palindromes with length <= N-2*i, not all a's
    }
    cout << 0;
}

int main() {
    io();
    int T; cin >> T;
    FOR(i,1,T+1) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }
}
/* 
* (Actually read this pls)
    * Rlly bad errors: int overflow, array bounds
    * Less bad errors: special cases (n=1?), set tle
    * Common sense: do smth instead of nothing
*/