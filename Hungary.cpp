/// Hungary and Hungary Tree
/// UVa 11419

#include <cstdio>
#include <cstring>
#define MEM(array) memset(array, 0, sizeof array)

const int MAXN = 1010;
int n, m, k;
bool graph[MAXN][MAXN];
int linker[MAXN];
bool used[MAXN];
bool inu[MAXN], inv[MAXN], usedu[MAXN], visu[MAXN], visv[MAXN];

bool dfs(int u) {
    for (int v = 1; v <= m; v++) {
        if (graph[u][v] && !used[v]) {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v])) {
                linker[v] = u;
                usedu[u] = true;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    memset(linker, -1, sizeof linker);
    int rst = 0;
    for (int u = 1; u <= n; u++) {
        memset(used, 0, sizeof used);
        if (dfs(u))
            rst++;
    }
    return rst;
}

bool makeTree(int u) {
    visu[u] = true;
    for (int v = 1; v <= m; v++) {
        if (graph[u][v] && !visv[v]) {
            visv[v] = true;
            if (linker[v] == -1 || makeTree(linker[v])) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3 && n) {
        MEM(graph);
        MEM(inu);
        MEM(inv);
        MEM(visu);
        MEM(visv);
        MEM(usedu);
        for (int i = 0; i < k; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            graph[a][b] = true;
            inu[a] = true;
            inv[b] = true;
        }
        printf("%d", hungary());
        for (int i = 1; i <= n; i++)
            if(!usedu[i])
                makeTree(i);
        for (int i = 1; i <= n; i++)
            if (!visu[i] && inu[i])
                printf(" r%d", i);
        for (int i = 1; i <= m; i++)
            if (visv[i] && inv[i])
                printf(" c%d", i);
        printf("\n");
    }
    return 0;
}
