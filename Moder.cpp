/// Moder
/// HYSBZ 1008
#include <cstdio>
class Moder {
    typedef long long LL;
private:
    LL _MOD;
public:
    LL plus(LL a, LL b) {
        return (a%_MOD + b%_MOD) % _MOD;
    }
    LL minus(LL from, LL with) {
        return ((from%_MOD - with%_MOD) % _MOD + _MOD) % _MOD;
    }
    LL multi(LL a, LL b) {
        LL rst = 0;
        while (b > 0) {
            if (b & 1) {
                rst = plus(rst, a);
            }
            a = plus(a, a);
            b >>= 1;
        }
        return rst;
    }
    LL pow(LL base, LL exp) {
        LL rst = 1;
        while (exp > 0) {
            if (exp & 1) {
                rst = multi(rst, base);
            }
            base = multi(base, base);
            exp >>= 1;
        }
        return rst;
    }
    LL modInverse(const LL b) {
        return pow(b, _MOD - 2);
    }
    LL divided(const LL from, const LL by) {
        return multi(from%_MOD, modInverse(by));
    }
    LL operator= (const LL mod) {
        return _MOD = mod;
    }
} moder;

int main() {
    moder = 100003;
    long long m, n;
    scanf("%lld%lld", &m, &n);
    printf("%lld\n", moder.minus(moder.pow(m, n), moder.multi(m, moder.pow(m - 1, n - 1))));
}
