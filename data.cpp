// compile: g++ -o data data.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
// run: ./data < data.in
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#include <debug/codeforces.h>
#define debug(x...) {_variables(#x);_print(x);}
#else
#define debug(x...)
#endif
template<typename...Args> void print_(Args...args){((cout<<args<<" "),...)<<endl;}
#define rep(i,a,b) for(int i=(a);i<(int)(b);++i)
#define sz(v) ((int)(v).size())
#define print(...) print_(__VA_ARGS__);
#define INTMAX (int)(9223372036854775807)
#define INTINF (int)(1152921504606846976)
#define int long long
#define MAXN 1010

set<tuple<int, int, int>> E;
int n, m;
vector<vector<int>> e;
vector<int> hasKey;

void bfs(int s, vector<int> &dis, vector<int> &vis) {
    queue<int> q; q.push(s); vis[s] = 1; dis[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: e[u]) {
            if (vis[v]) continue;
            vis[v] = 1;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int ks; cin >> n >> m >> ks;
    hasKey.assign(n, 0);
    rep(i, 0, ks) {
        int t; cin >> t;
        hasKey[t] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, t; cin >> u >> v >> t;
        E.insert({u, v, t});
    }
    // map (u, i) to u + i*n
    e.resize(2*n);
    auto add_edge = [&](pair<int, int> u, pair<int, int> v) {
        e[u.first + u.second*n].push_back({v.first + v.second*n});
    };
    // U = E - T
    for (auto [u, v, t]: E) {
        // (u,v) in L, v in K
        if (t && hasKey[v]) add_edge({u, 1}, {v, 0}), add_edge({u, 1}, {v, 1});
        // (u,v) in L, v not in K
        if (t && !hasKey[v]) add_edge({u, 1}, {v, 0});
        // (u,v) not in L, v in K
        if (!t && hasKey[v]) add_edge({u, 0}, {v, 0}), add_edge({u, 0}, {v, 1}), add_edge({u, 1}, {v, 1});
        // (u,v) not in L, v not in K
        if (!t && !hasKey[v]) add_edge({u, 0}, {v, 0}), add_edge({u, 1}, {v, 1});
    }
    vector<int> dis(2*n, INTINF), vis(2*n, 0);
    bfs(n * hasKey[0], dis, vis);
    int ans = min(dis[n-1], dis[2*n-1]);
    cout << (ans==INTINF ? -1 : ans) << endl;

    return 0;
}
