/// LCA倍增
/// HDU 2586
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LOG = 20, MAXN = 40010;
struct Edge
{
    int v;
    int w;
    int next;
} e[MAXN * 2];
int head[MAXN], coe;
int parent[MAXN][LOG], dep[MAXN], len[MAXN];
int n, m;

void addEdge(int u, int v, int w) {
    e[coe].v = v;
    e[coe].w = w;
    e[coe].next = head[u];
    head[u] = coe++;
}

void dfs(int u, int father, int depth, int length) {
    dep[u] = depth;
    len[u] = length;
    parent[u][0] = father;
    for (int i = 1; i < LOG; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (e[i].v != father) {
            dfs(e[i].v, u, depth + 1, length + e[i].w);
        }
    }
}

int up(int x, int step) {
    for (int i = 0; i < LOG; i++) {
        if (step&(1 << i)) {
            x = parent[x][i];
        }
    }
    return x;
}

int LCA(int na, int nb) {
    if (dep[na] > dep[nb])
        std::swap(na, nb);
    nb = up(nb, dep[nb] - dep[na]);
    if (na == nb)
        return na;
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[na][i] != parent[nb][i]) {
            na = parent[na][i];
            nb = parent[nb][i];
        }
    }
    return parent[na][0];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(head, -1, sizeof head);
        coe = 0;
        scanf("%d%d", &n, &m);
        while (--n) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        dfs(1, 1, 0, 0);
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            int p = LCA(a, b);
            printf("%d\n", len[a] + len[b] - len[p] * 2);
        }
    }
    return 0;
}
