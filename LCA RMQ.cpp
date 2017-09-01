/// LCA RMQ
#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 10010, LOG = 20;

struct Edge
{
    int v;
    int w;
    int next;
} e[MAXN * 2];
int head[MAXN], coe;
int dis[MAXN];
int preorder[MAXN * 2], dep[MAXN * 2], copre, fst[MAXN];
int dp[MAXN][LOG];
int n, m, c;

inline int minDep(int i, int j) {
    return dep[i] < dep[j] ? i : j;
}

void addEdge(int u, int v, int w) {
    e[coe].v = v;
    e[coe].w = w;
    e[coe].next = head[u];
    head[u] = coe++;
}

void dfs(int u, int fa, int d, int distance) {
    dis[u] = distance;
    preorder[copre] = u;
    dep[copre] = d;
    fst[u] = copre;
    copre++;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (e[i].v != fa) {
            dfs(e[i].v, u, d + 1, distance + e[i].w);
            preorder[copre] = u;
            dep[copre] = d;
            copre++;
        }
    }
}

void makeRMQ() {
    for (int i = 0; i < copre; i++) {
        dp[i][0] = i;
    }
    for (int j = 1; (1 << j) <= copre; j++) {
        for (int i = 0; i + (1 << j) - 1 < copre; i++) {
            dp[i][j] = minDep(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = log2(r - l + 1);
    return minDep(dp[l][k], dp[r - (1 << k) + 1][k]);
}

int LCA(int a, int b) {
    if (fst[a] < fst[b])
        return preorder[query(fst[a], fst[b])];
    else
        return preorder[query(fst[b], fst[a])];
}
