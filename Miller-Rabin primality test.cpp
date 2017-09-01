/// Miller-Rabin primality test
/// hihoCoder 1287
#include <cstdio>

long long fastMuti(long long a, long long b, const long long mod) {
    long long rst = 0;
    while (b > 0) {
        if (b & 1LL) {
            rst += a;
            rst %= mod;
        }
        a += a;
        a %= mod;
        b >>= 1;
    }
    return rst;
}

long long fastPow(long long base, long long exp, const long long mod) {
    long long rst = 1;
    while (exp > 0) {
        if (exp & 1LL) {
            rst = fastMuti(rst, base, mod);
        }
        base = fastMuti(base, base, mod);
        exp >>= 1;
    }
    return rst;
}

bool millerrabin(const long long n) {
    const int a[12] = { 2,3,5,7,11,13,17,19,23,29,31,37 };
    for (int ai = 0; ai < 12 && a[ai] < n; ai++) {
        long long exp = n - 1;
        exp>>=1;
        while ((exp & 1LL) == 0) {
            long long auth = fastPow(a[ai], exp, n);
            if (auth == n - 1 || auth==1 && exp<((n-1)>>1))
                break;
            exp >>= 1;
        }
        if(exp&1LL) {
            long long auth = fastPow(a[ai], exp, n);
            if (auth != n - 1 && auth!=1)
                return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n;
        scanf("%lld", &n);
        puts(millerrabin(n) ? "Yes" : "No");
    }
}
