/// Cantor expansion
/// CSU 1828
#include <cstdio>
typedef long long LL;

char str[10];
LL fact[9] = {1,1,2,6,24,120,720,5040,40320};

LL cantor() {
    LL rst = 0;
    for (int i = 0; i < 9; i++) {
        int counted = 0;
        for (int j = i + 1; j < 9; j++) {
            if (str[i] > str[j])
                counted++;
        }
        rst += counted*fact[8 - i];
    }
    return rst;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", str);
        printf("%lld\n", cantor()+1);
    }
}
