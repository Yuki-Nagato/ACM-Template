/// LCA Tarjan
/// HDU 2874
#include <cstdio>
#include <cstring>

const int MAXN = 10010;

struct Edge
{
    int v;
    int w;
    int next;
} e[MAXN*2];
int head[MAXN], coe;
int fa[MAXN];
int rt[MAXN];
bool vis[MAXN];
int dis[MAXN];
struct Query
{
    int b;
    int n;
    int next;
} query[2000000];
int qhead[MAXN], coq;
int ans[1000000];
int n, m, c;

void addEdge(int u, int v, int w) {
    e[coe].v = v;
    e[coe].w = w;
    e[coe].next = head[u];
    head[u] = coe++;
}
void addQuery(int a, int b, int n) {
    query[coq].b = b;
    query[coq].n = n;
    query[coq].next = qhead[a];
    qhead[a] = coq++;
}

int find(int x) {
    if(fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}

void tarjan(int u, int distance, int root) {
    vis[u] = true;
    dis[u] = distance;
    fa[u] = u;
    rt[u] = root;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (!vis[e[i].v]) {
            tarjan(e[i].v, distance + e[i].w, root);
            fa[e[i].v] = u;
        }
    }
    for (int i = qhead[u]; i != -1; i = query[i].next) {
        if (vis[query[i].b]) {
            ans[query[i].n] = (root==rt[query[i].b]?dis[u]+dis[query[i].b]-dis[find(query[i].b)]*2:-1);
        }
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &c) == 3) {
        memset(head, -1, sizeof head);
        memset(qhead, -1, sizeof qhead);
        memset(ans, -1, sizeof ans);
        memset(vis, 0, sizeof vis);
        coe = 0; coq = 0;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        for (int i = 0; i < c; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            addQuery(a, b, i);
            addQuery(b, a, i);
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                tarjan(i, 0, i);
            }
        }
        for (int i = 0; i < c; i++) {
            if (ans[i] == -1)
                printf("Not connected\n");
            else
                printf("%d\n", ans[i]);
        }
    }
    return 0;
}
