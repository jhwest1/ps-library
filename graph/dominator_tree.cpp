#include <bits/stdc++.h>
using namespace std;

const int MAXV = 101010;

int n, m;
vector<int> g[MAXV], r[MAXV];

int dn, ln[MAXV], rv[MAXV], par[MAXV];
void dfs(int v) {
    ln[v] = ++dn;
    rv[dn] = v;
    for (int x : g[v]) if (!ln[x]) 
        par[x] = v, dfs(x);
}

int sdom[MAXV], idom[MAXV];
vector<int> qr[MAXV];

struct dsu {
    int par[MAXV], val[MAXV];

    void init() { iota(par, par + MAXV, 0); iota(val, val + MAXV, 0); }
    int eval(int v) { // returns the vertex id with smallest sdom
        if (par[v] != v) {
            int x = eval(par[v]);
            val[v] = (sdom[val[v]] < sdom[x]) ? val[v] : x;
            par[v] = par[par[v]];
        }
        return val[v];
    }
    void link(int p, int v) { par[v] = p; }
} d1;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        r[v].push_back(u);
    }
    dfs(1);

    d1.init();
    for (int i = 1; i <= n; i++) sdom[i] = 1e9;

    // compute sdom in reverse dfs order
    for (int i = n; i > 1; i--) {
        int v = rv[i];
        if (v == 0) continue; 
        for (int x : r[v]) if (ln[x]) {
            if (ln[x] > ln[v]) sdom[v] = min(sdom[v], sdom[d1.eval(x)]);
            else sdom[v] = min(sdom[v], ln[x]);
        }
        d1.link(par[v], v);
        qr[rv[sdom[v]]].push_back(v); 
        for (int x : qr[par[v]]) {
            int y = d1.eval(x);
            if (sdom[x] == sdom[y]) idom[x] = rv[sdom[x]]; 
            else idom[x] = y; 
        }
    }
    // compute idom
    for (int i = 2; i <= n + 1; i++) {
        int v = rv[i];
        if (v == 0) continue;
        if (idom[v] != rv[sdom[v]]) idom[v] = idom[idom[v]]; 
    }
}