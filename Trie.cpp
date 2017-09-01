/// Trie
/// HDU 1251
#include <cstdio>
#include <cstring>

const int MAXN = 1000000;

struct Trie {
    static const int SIGMA_SIZE = 26;
    int ch[MAXN][SIGMA_SIZE];
    int val[MAXN];
    int sz;
    Trie() :sz(1) {}
    int idx(char c) {
        return c - 'a';
    }
    void insert(char s[]) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int ha = idx(s[i]);
            if (ch[u][ha] == 0) {
                //memset(ch[sz], 0, sizeof ch[sz]);
                //val[sz] = 0;
                ch[u][ha] = sz++;
            }
            u = ch[u][ha];
            val[u]++;
        }
        //val[u] = v;
    }
    int find(char s[]) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int ha = idx(s[i]);
            if (ch[u][ha] == 0)
                return 0;
            u = ch[u][ha];
        }
        return val[u];
    }
} trie;

char str[20];

#ifdef LOCAL_DEBUG
#define gets(buff) gets_s(buff)
#endif // LOCAL_DEBUG


int main() {
    while (gets(str) != NULL && str[0] != '\0') {
        trie.insert(str);
    }
    while (gets(str) != NULL) {
        printf("%d\n", trie.find(str));
    }
    return 0;
}
