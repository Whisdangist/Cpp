#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp) ((void)0)
#endif

/* 最优二叉搜索树问题 p226 */

unsigned int N;
double p[101], q[101];
double  e[102][102], w[102][102];
unsigned int root[101][101];  // suppose N <= 100

// dynamic programming: buttom-up method
// 这个函数只是抄了一遍书上的伪代码，实际运行会出错
void dp_bu() {
	for (int l = 1; l <= N; l++) {
		for (int i = 1; i <= N-l+1; l++) {
			int j = i+l-1;
			e[i][j] = 0xFFFFFFFF;
			ASSERT(w[i][j-1] != 0);
			w[i][j] = w[i][j-1] + p[j] + q[j];
			for (int r = i; r <= j; r++) {
				ASSERT(e[i][r-1] != 0);
				ASSERT(e[r+1][j] != 0);
				double t = e[i][r-1] + e[r+1][j] + w[i][j];
				if (t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

double prob(int i, int j) {
	if (w[i][j] == 0) {
		w[i][j] = prob(i, j-1) + p[j] + q[j];
	}
	return w[i][j];
}

// dynamic programming: top-down with memoization
double dp_td(int i, int j) {
	if (e[i][j] == 0) {
		e[i][j] = 0xFFFFFFFF;
		for (int r = i; r <= j; r++) {
			double t = dp_td(i, r-1) + dp_td(r+1, j) + prob(i, j);
			if (e[i][j] > t) {
				e[i][j] = t;
				root[i][j] = r;
			}
		}
	}
	return e[i][j];
}


void solve() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> p[i];
	}
	for (int i = 0; i <= N; i++) {
		cin >> q[i];
	}

	memset(e, 0, sizeof(e));
	memset(w, 0, sizeof(w));
	for (int i = 1; i <= N+1; i++) {
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}

	cout << dp_td(1, N) << endl;

	// 照搬书上伪代码自底向上行不通 运行会出现 Assertion failed!
	// dp_bu();
	// cout << e[1][N] << endl;
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	#endif

	solve();
	
	#ifdef OFFLINE
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
