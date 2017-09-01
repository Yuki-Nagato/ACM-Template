/// Dinic
/// HDU 1532
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const int MAXN = 210;

struct Edge
{
    int v;
    int w;
    int next;
} e[MAXN*MAXN];
int head[MAXN], coe;
int dis[MAXN];
int n, m;
int source, convergence;
//bool dayExist[501];
int sumDays;
int que[MAXN*MAXN], qhead, qback;

inline void addEdge(int u, int v, int w) {
    e[coe].v = v;
    e[coe].w = w;
    e[coe].next = head[u];
    head[u] = coe++;
}

bool dinic_bfs() {
    memset(dis, -1, sizeof dis);
    dis[source] = 0;
    //std::queue<int> que;
    qhead = 0; qback = 0;
    que[qback++] = source;
    while (qhead<qback) {
        //int i = que.front();
        //que.pop();
        int i = que[qhead++];
        for (int j = head[i]; j!=-1; j=e[j].next) {
            if (dis[e[j].v] < 0 && e[j].w > 0) {
                dis[e[j].v] = dis[i] + 1;
                //que.push(e[j].v);
                que[qback++] = e[j].v;
            }
        }
    }
    return dis[convergence] > 0;
}

int dinic_find(int x, int low) {
    if (low <= 0)
        return false;
    if (x == convergence)
        return low;
    int cost = 0;
    for (int i = head[x]; i != -1; i=e[i].next) {
        if (e[i].w > 0 && dis[e[i].v] == dis[x] + 1) {
            int a = dinic_find(e[i].v, std::min(low-cost, e[i].w));
            if (a > 0) {
                cost += a;
                e[i].w -= a;
                e[i^1].w += a;
                if (cost >= low)
                    break;
            }
            else {
                dis[e[i].v] = -1;
            }
        }
    }
    return cost;
}

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        source = 1; convergence = n;
        memset(head, -1, sizeof head);
        coe = 0;
        while (m--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, c);
            addEdge(b, a, 0);
        }
        int ans = 0;
        while (dinic_bfs()) {
            int tans;
            while (tans = dinic_find(1, 0x3f3f3f3f))
                ans += tans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
