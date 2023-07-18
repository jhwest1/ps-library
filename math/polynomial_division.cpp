#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> cx;
const double PI = acos(-1);
const double eps = 1e-10;

void dft(vector<cx> &f, bool inv) {
    int n = f.size();
    int b = __lg(n);
    vector<int> r(n);
    for (int i = 0; i < n; i++) 
        r[i] = (r[i / 2] | (i & 1) << b) >> 1;
    for (int i = 0; i < n; i++)
        if (r[i] > i) swap(f[i], f[r[i]]);

    for (int d = 1; d < n; d *= 2) {
        double ang = inv ? (-PI / d) : (PI / d);
        for (int i = 0; i < n; i += 2 * d) {
            for (int j = 0; j < d; j++) {
                cx w = { cos(ang * j), sin(ang * j) };
                cx s = f[i + j];
                cx t = f[i + j + d] * w;

                f[i + j] = s + t;
                f[i + j + d] = s - t;
            }
        }
    }
}
vector<double> multiply(vector<double> f, vector<double> g) {
    int sz = f.size() + g.size();
    int n = 1 << (__lg(sz - 1) + 1);
    f.resize(n);
    g.resize(n);
    vector<cx> F(n), G(n);
    for (int i = 0; i < n; i++) {
        F[i].real(f[i]);
        G[i].real(g[i]);
    }
    dft(F, false);
    dft(G, false);
    for (int i = 0; i < n; i++) F[i] = F[i] * G[i];
    dft(F, true);
    vector<double> result(n);
    for (int i = 0; i < n; i++) result[i] = F[i].real() / n;
    while (!result.empty() && abs(result.back()) < eps)
        result.pop_back();
    return result;
}
vector<double> inverse_series(vector<double> f, int k) {
    vector<double> result = {1 / f[0]};
    for (int i = 1; i <= __lg(k); i++) {
        auto tmp = multiply(result, f);
        tmp[0] = 2 - tmp[0];
        for (int i = 1; i < tmp.size(); i++)
            tmp[i] = -tmp[i];

        result = multiply(result, tmp);
        result.resize(1 << i);
    }
    result.resize(k);
    return result;
}
vector<double> divide(vector<double> f, vector<double> g) {
    reverse(f.begin(), f.end());
    reverse(g.begin(), g.end());
    int sz = f.size() - g.size() + 1;
    auto result = multiply(f, inverse_series(g, sz));
    result.resize(sz);
    reverse(result.begin(), result.end());
    return result;
}
int main() {
    vector<double> f = {63, 86, 23, 77, 43, 25, 76, 88, 99, 12};
    vector<double> g = {5, 6, 6, 8, 3, 6, 2};
    auto result = divide(f, g);

    result = multiply(result, g);
    for (double x : result)
        cout << x << ' ';
}