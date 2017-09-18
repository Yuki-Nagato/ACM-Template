/// AC Automation
/// HDU 2222
#include <cstdio>
#include <cstring>
#include <queue>

struct Trie {
	static const int MAXND = 10000*50;
	static const int SIGMA_SIZE = 26;
	int ch[MAXND][SIGMA_SIZE];
	int val[MAXND];
	int sz;
	Trie() :sz(1) {}
	void init() {
		sz = 1;
		memset(ch[0], 0, sizeof ch[0]);
	}
	int idx(char c) {
		return c - 'a';
	}
	void insert(char s[]) {
		int u = 0;
		for (int i = 0; s[i]; i++) {
			int ha = idx(s[i]);
			if (ch[u][ha] == 0) {
				memset(ch[sz], 0, sizeof ch[sz]);
				val[sz] = 0;
				ch[u][ha] = sz++;
			}
			u = ch[u][ha];
			//val[u]++;
		}
		val[u]++;
	}
};

struct ACAutomation :Trie {
	int fail[MAXND];
	int last[MAXND];
	void makeFail() {
		std::queue<int> que;
		fail[0] = 0;
		last[0] = 0;
		for (int i = 0; i < SIGMA_SIZE; i++) {
			int u = ch[0][i];
			if (u) {
				fail[u] = 0;
				last[u] = 0;
				que.push(u);
			}
		}
		while (!que.empty()) {
			int r = que.front();
			que.pop();
			for (int i = 0; i < SIGMA_SIZE; i++) {
				int u = ch[r][i];
				if (u == 0) {
					continue;
				}
				que.push(u);
				int v = fail[r];
				while (v&&ch[v][i] == 0)
					v = fail[v];
				fail[u] = ch[v][i];
				last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
			}
		}
	}
	int found(int j) {
		int sum = 0;
		while (j) {
			sum += val[j];
			val[j] = 0;
			j = last[j];
		}
		return sum;
	}
	int find(char str[]) {
		int j = 0, rst = 0;
		for (int i = 0; str[i]; i++) {
			int ha = idx(str[i]);
			while(j&&ch[j][ha]==0)
				j = fail[j];
			j = ch[j][ha];
			if (val[j])
				rst += found(j);
			else if (last[j])
				rst += found(last[j]);
		}
		return rst;
	}
} aca;

const int MAXN = 1000000+10;
char buff[MAXN];
int n;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		aca.init();
		scanf("%d", &n);
		while (n--) {
			scanf("%s", buff);
			aca.insert(buff);
		}
		aca.makeFail();
		scanf("%s", buff);
		printf("%d\n", aca.find(buff));
	}
	return 0;
}
