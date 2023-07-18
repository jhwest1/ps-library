#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int MAXA = 26;

struct suffix_automaton {
	int len[2 * MAXN], sl[2 * MAXN], go[MAXA][2 * MAXN];
	int sz, r;
		
	int new_node() {
		for (int i = 0; i < 26; i++)
			go[i][sz] = -1;
		return sz++;
	}
	void init() { sl[0] = -1; new_node(); }
	void insert(int c) {
		int n = new_node();
		len[n] = len[r] + 1;
		for (int v = r; v != -1; v = sl[v]) {
			if (go[c][v] == -1) go[c][v] = n;
			else {
				int w = go[c][v];
				if (len[w] == len[v] + 1) sl[n] = w;
				else {
					int u = new_node();
					len[u] = len[v] + 1;
					sl[u] = sl[w];
					for (int i = 0; i < MAXA; i++)
						go[i][u] = go[i][w];
					
					sl[w] = sl[n] = u;
					while (v != -1 && go[c][v] == w) {
						go[c][v] = u;
						v = sl[v];
					}
				}
				break;
			} 
		}
		r = n;
	}
} t1;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    string s; cin >> s;
    t1.init();

    for (char ch : s)
        t1.insert(ch);
}