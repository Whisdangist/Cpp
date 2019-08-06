#include <bits/stdc++.h>
using namespace std;

/* 钢条切割问题 p204 */

int p[100], s[100];

// dynamic programming: buttom-up method
void dp_bu() {
	for (int j = 1; j <= 10; j++) {
		int q = -1;
		for (int i = 1; i <= j; i++) {
			if (q < p[i] + p[j-i]) {
				s[j] = i;
				q = p[i] + p[j-i];
			}
		}
		p[j] = q;
	}
}

// dynamic programming: top-down with memoization
int dp_td(int n) {
	if (p[n] != -1) {
		return p[n];
	}
	int q = -1;
	for (int i = 1; i < n; i++) {
		if (q < dp_td(i) + dp_td(n-i)) {
			s[n] = i;
			q = dp_td(i) + dp_td(n-i);
		}
	}
	p[n] = q;
	return q;
}

void solve() {
	memset(p, -1, sizeof(p));
	p[0] = 0;
	for (int i = 1; i <= 10; i++) {
		cin >> p[i];
	}

	dp_bu();
	
	for (int i = 0; i < 100; i++) {
		cout << "dp_td(" << i << ") = " << dp_td(i) << "\t";
		cout << "length: ";
		for (int tmp = i; tmp > 0; tmp -= s[tmp]) {
			cout << s[tmp] << " ";
		}
		cout << endl;
	}

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
