/// 模线性方程组
/// hihoCoder 1303
#include <cstdio>

int n;
long long m[1000], r[1000];

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = b;
        b = a%b;
        a = r;
    }
    return a;
}

long long extendGcd(long long a, long long b, long long& x, long long & y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        long long r = extendGcd(b, a%b, x, y);
        long long t = x;
        x = y;
        y = t - a / b*y;
        return r;
    }
}

long long solve() {
    long long M = m[0], R = r[0];
    for (int i = 1; i < n; i++) {
        long long c = r[i] - R;
        long long d = gcd(M, m[i]);
        if (c%d)
            return -1;
        long long x, y;
        extendGcd(M / d, m[i] / d, x, y);
        x = (c / d*x) % (m[i] / d);
        R += x*M;
        M = M / d*m[i];
        R %= M;
    }
    if (R < 0)
        R += M;
    return R;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld", m + i, r + i);
    }
    printf("%lld\n", solve());
    return 0;
}
