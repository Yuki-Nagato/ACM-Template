/// 矩阵快速幂
/// HDU 6198
#include "bits\stdc++.h"

typedef long long LL;
const LL MOD = 998244353;

struct Matrix {
	static const int N = 2;
	LL mat[N][N];
	Matrix() {}
	Matrix(const LL* value) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mat[i][j] = *(value + i*N + j);
			}
		}
	}
	void init() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				mat[i][j] = (i == j);
			}
		}
	}
	Matrix operator* (const Matrix& b) const {
		Matrix rst;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				rst.mat[i][j] = 0;
				for (int k = 0; k < N; k++) {
					rst.mat[i][j] += mat[i][k] * b.mat[k][j] % MOD;
					rst.mat[i][j] %= MOD;
				}
			}
		}
		return rst;
	}
	friend Matrix operator^ (Matrix base, LL exp) {
		Matrix rst;
		rst.init();
		while (exp) {
			if (exp & 1)
				rst = rst*base;
			exp >>= 1;
			base = base*base;
		}
		return rst;
	}
};

int main() {
	int k;
	LL temp[] = { 1,1,1,0 };
	while (scanf("%d", &k) == 1) {
		Matrix lambda(temp);
		Matrix ans = lambda ^ (2 * (k + 1));
		printf("%lld\n", ans.mat[0][0] - 1);
	}
	return 0;
}
