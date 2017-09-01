/// Binary Indexed Tree
/// 51NOD 1107
#include <cstdio>
#include <algorithm>
#include <map>

template <class T>
class BinaryIndexedTree
{
public:
    BinaryIndexedTree(int MAX_N) :MAX_N(MAX_N) {
        BIT = new T[MAX_N + 2]();
    }
    ~BinaryIndexedTree() {
        delete[] BIT;
    }
    void build(T A[]) {
        for (int i = 1; i <= MAX_N; i++) {
            BIT[i] = A[i];
            for (int j = i - 1; j>i - lowbit(i); j--)
                BIT[i] += A[j];
        }
    }
    void edit(int i, T delta) {
        while (i <= MAX_N) {
            BIT[i] += delta;
            i += lowbit(i);
        }
    }
    T sum(int i) {
        T ans = 0;
        while (i > 0) {
            ans += BIT[i];
            i -= lowbit(i);
        }
        return ans;
    }

private:
    int MAX_N;
    T* BIT;
    int lowbit(int x) {
        return x&(-x);
    }
};

struct Point
{
    int x, y;
} p[50000];
int n;
bool cmp(const Point& a, const Point& b) {
    if (a.x != b.x)
        return a.x > b.x;
    else
        return a.y > b.y;
}

int main() {
    scanf("%d", &n);
    std::map<int, int> reflect;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
        reflect[p[i].y];
    }
    std::sort(p, p + n, cmp);
    int coy = 0;
    for (auto& it : reflect) {
        it.second = ++coy;
    }
    BinaryIndexedTree<int> c(coy+1);
    int rst = 0;
    for (int i = 0; i < n; i++) {
        rst += c.sum(reflect[p[i].y]);
        c.edit(reflect[p[i].y] + 1, 1);
    }
    printf("%d\n", rst);
    return 0;
}
