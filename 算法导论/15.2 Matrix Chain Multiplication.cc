#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp)
#endif

/* 矩阵链乘法问题 p210 */

unsigned int a[7];
unsigned int p[7][7];
unsigned int s[7][7];

// dynamic programming: top-down with memoization
int dp_td(int m, int n) {
	if (p[m][n] != -1) {
		return p[m][n];
	}
	for (int k = n; k >= m+1; k--) {
		int tmp = dp_td(m, k-1) + dp_td(k, n) + a[m-1]*a[k-1]*a[n];
		if (p[m][n] > tmp) {
			s[m][n] = k;
			p[m][n] = tmp;
		}
	}
	return p[m][n];
}

void print(int m, int n) {
	if (m == n) {
		cout << m;
		return;
	}
	cout << "(";
	ASSERT(s[m][n] != 0);
	if (s[m][n] == n) {
		for (int i = m; i <= n; i++) {
			cout << i;
		}
	}
	else {
		print(m, s[m][n]-1);
		print(s[m][n], n);
	}
	cout << ")";
}

void solve() {
	memset(p, -1, sizeof(p));
	for (int i = 0; i < 7; i++) {
		cin >> a[i];
		p[i][i] = 0;
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			dp_td(i, j);
		}
	}
	for (int i = 1; i <= 6; i++) {
		for (int j = i+2; j <= 6; j++) {
			print(i, j);
			cout << endl;
		}
	}
	cout << endl;
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	#endif

	solve();
	
	#ifdef OFFLINE
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
