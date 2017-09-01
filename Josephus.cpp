/// Josephus
/// hihoCoder 1296
#include <stdio.h>

int josephus(int n, int k) {
    if (n == 1)
        return 0;
    if (n < k) {
        int ret = 0;
        for (int i = 2; i <= n; i++) {
            ret += k;
            ret %= i;
        }
        return ret;
    }
    int ret = josephus(n - n / k, k);
    if (ret < n%k)
        ret += n - n%k;
    else
        ret += (ret - n%k) / (k - 1) - n%k;
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", josephus(n, k));
    }
}
