#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct point {
    int x, y;
};
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator+(point a, point b) { return {a.x + b.x, a.y + b.y}; }
ll operator/(point a, point b) { return (ll)a.x * b.y - (ll)a.y * b.x; }
ll operator*(point a, point b) { return (ll)a.x * b.x + (ll)a.y * b.y; }

int ccw(point a, point b, point c) {
    ll x = (b - a) / (c - a);
    return (x > 0) - (x < 0);
}
// is P on segment (S, E)
bool point_on_line(point P, point S, point E) {
    return ccw(S, E, P) == 0 &&
        0 <= (P - S) * (E - S) && (P - S) * (E - S) <= (E - S) * (E - S);
}
// 0 : two segments do not touch or intersect
// 1 : two segments touch at one of their endpoints
// 2 : two segments cross each other
// 3 : two segments overlap
int intersect(point s1, point e1, point s2, point e2) {
    if (ccw(s1, e1, s2) == 0 && ccw(s1, e1, e2) == 0) {
        ll L = (s2 - s1) * (e1 - s1);
        ll R = (e2 - s1) * (e1 - s1);
        if (L > R) swap(L, R);
        if (R < 0 || L > (e1 - s1) * (e1 - s1)) return 0;
        if (R == 0 || L == (e1 - s1) * (e1 - s1)) return 1;
        return 3;
    }
    if (ccw(s1, e1, s2) * ccw(s1, e1, e2) < 0 &&
        ccw(s2, e2, s1) * ccw(s2, e2, e1) < 0) return 2;
    if (point_on_line(s2, s1, e1) || point_on_line(e2, s1, e1) ||
        point_on_line(s1, s2, e2) || point_on_line(e1, s2, e2)) return 1;
    return 0;
}
