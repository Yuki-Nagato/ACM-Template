/// Segment tree
/// HDU 1698
#include <cstdio>

const int MAXN = 100000 + 10;
int n, m;
int sum[MAXN << 2];
int lazy[MAXN << 2];
int len[MAXN << 2];

inline int ls(const int ROOT) {
    return ROOT << 1;
}
inline int rs(const int ROOT) {
    return ls(ROOT) | 1;
}
inline void pushUp(const int ROOT) {
    sum[ROOT] = sum[ls(ROOT)] + sum[rs(ROOT)];
}
inline void pushDown(const int ROOT) {
    if (lazy[ROOT]) {
        sum[ls(ROOT)] = lazy[ROOT] * len[ls(ROOT)];
        sum[rs(ROOT)] = lazy[ROOT] * len[rs(ROOT)];
        lazy[ls(ROOT)] = lazy[ROOT];
        lazy[rs(ROOT)] = lazy[ROOT];
        lazy[ROOT] = 0;
    }
}
void build(const int ROOT, const int L, const int R) {
    len[ROOT] = R - L + 1;
    lazy[ROOT] = 0;
    if (L == R) {
        sum[ROOT] = 1;
        return;
    }
    const int M = (L + R) >> 1;
    build(ls(ROOT), L, M);
    build(rs(ROOT), M + 1, R);
    pushUp(ROOT);
}
void update(const int l, const int r, const int val, const int ROOT, const int L, const int R) {
    if (r<L || l>R)
        return;
    if (l <= L && R <= r) {
        sum[ROOT] = val*len[ROOT];
        lazy[ROOT] = val;
        return;
    }
    pushDown(ROOT);
    const int M = (L + R) >> 1;
    update(l, r, val, ls(ROOT), L, M);
    update(l, r, val, rs(ROOT), M + 1, R);
    pushUp(ROOT);
}
int query(const int l, const int r, const int ROOT, const int L, const int R) {
    if (r<L || l>R)
        return 0;
    if (l <= L && R <= r)
        return sum[ROOT];
    pushDown(ROOT);
    const int M = (L + R) >> 1;
    return query(l, r, ls(ROOT), L, M) + query(l, r, rs(ROOT), M + 1, R);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++) {
        scanf("%d%d", &n, &m);
        build(1, 1, n);
        while (m--) {
            //printf("debug: %d\n", query(1, n, 1, 1, n));
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, 1, n);
        }
        printf("Case %d: The total value of the hook is %d.\n", cs, query(1, n, 1, 1, n));
    }
    return 0;
}
