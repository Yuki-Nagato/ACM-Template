/// Dancing Link
/// hihoCoder 1317
#include <cstdio>

const int MAXN = 101 * 101;
bool board[101][101];
int n, m;
int L[MAXN], R[MAXN], U[MAXN], D[MAXN], C[MAXN], S[101], con;

void build() {
	for (con = 0; con <= m; con++) {
		U[con] = D[con] = con;
		L[con] = con - 1;
		R[con] = con + 1;
		S[con] = 0;
	}
	L[0] = m;
	R[m] = 0;
	for (int i = 1; i <= n; i++) {
		int lastLeft = 0;
		for (int j = 1; j <= m; j++) {
			if (board[i][j]) {
				// D and U
				D[con] = j;
				U[con] = U[j];
				D[U[j]] = con;
				U[j] = con;
				C[con] = j;
				S[j]++;
				// R and L
				if (lastLeft == 0) {
					lastLeft = con;
					L[con] = con;
					R[con] = con;
				}
				else {
					R[con] = R[lastLeft];
					L[con] = lastLeft;
					L[R[lastLeft]] = con;
					R[lastLeft] = con;
				}
				con++;
			}
		}
	}
}

void remove(int c) {
	L[R[c]] = L[c];
	R[L[c]] = R[c];
	for (int i = D[c]; i != c; i = D[i]) {
		for (int j = R[i]; j != i; j = R[j]) {
			U[D[j]] = U[j];
			D[U[j]] = D[j];
			S[C[j]]--;
		}
	}
}

void resume(int c) {
	for (int i = U[c]; i != c; i = U[i]) {
		for (int j = L[i]; j != i; j = L[j]) {
			S[C[j]]++;
			U[D[j]] = j;
			D[U[j]] = j;
		}
	}
	L[R[c]] = c;
	R[L[c]] = c;
}

bool dfs() {
	if (R[0] == 0) {
		return true;
	}
	int idx, minnum = 0x3f3f3f3f;
	for (int i = R[0]; i != 0; i = R[i]) {
		if (S[i] < minnum) {
			minnum = S[i];
			idx = i;
		}
	}
	remove(idx);
	for (int i = D[idx]; i != idx; i = D[i]) {
		for (int j = R[i]; j != i; j = R[j]) {
			remove(C[j]);
		}
		if (dfs()) {
			return true;
		}
		for (int j = L[i]; j != i; j = L[j]) {
			resume(C[j]);
		}
	}
	resume(idx);
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				getchar();
				board[i][j] = getchar() == '1';
			}
		}
		build();
		puts(dfs() ? "Yes" : "No");
	}
	return 0;
}
