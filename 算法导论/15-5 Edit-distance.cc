#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#include <windows.h>
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))

#define MAX_N 1000

/* 编辑距离问题 p232 */

int p[MAX_N][MAX_N], route[MAX_N][MAX_N];
bool mask[MAX_N][MAX_N];
char x[MAX_N], y[MAX_N];
int m, n;
int cost[6];

int dp(int ii, int jj) {
	if (ii > m) {
		int last_cost = 0;
		for (; jj <= n; jj++) {
			// insert
			last_cost += cost[3];
		}
		return last_cost;
	}
	if (mask[ii][jj]) {
		return p[ii][jj];
	}

	int t[6] = {INF, INF, INF, INF, INF, INF};
	// copy
	if (x[ii] == y[jj] && jj <= n) {
		t[0] = dp(ii+1, jj+1) + cost[0];
	}
	// replace
	if (jj <= n) {
		t[1] = dp(ii+1, jj+1) + cost[1];
	}
	// delete
	if (jj <= n) {
		t[2] = dp(ii+1, jj) + cost[2];
	}
	// insert
	if (jj <= n) {
		t[3] = dp(ii, jj+1) + cost[3];
	}
	// twiddle
	if (ii+1 <= m && jj+1 <= n && x[ii] == y[jj+1] && x[ii+1] == y[jj]) {
		t[4] = dp(ii+2, jj+2);
	}
	// kill
	if (jj > n) {
		t[5] = dp(m+1, n+1);
	}
	int min_cost = INF;
	for (int iii = 0; iii < 6; iii++) {
		if (t[iii] < min_cost) {
			min_cost = t[iii];
			route[ii][jj] = iii;
		}
	}
	mask[ii][jj] = true;
	p[ii][jj] = min_cost;
	return min_cost;
}

void print(int i, int j) {
	if (i > m) {
		for (; j <= n; j++) {
			cout << "insert  " << endl;
		}
		return;
	}
	ASSERT(route[i][j] != -1);
	switch (route[i][j]) {
	case 0:  // copy
		cout << "copy    " << endl;
		print(i+1, j+1);
		break;
	case 1:  // replace
		cout << "replace " << endl;
		print(i+1, j+1);
		break;
	case 2:  // delete
		cout << "delete  " << endl;
		print(i+1, j);
		break;
	case 3:  // insert
		cout << "insert  " << endl;
		print(i, j+1);
		break;
	case 4:  // twiddle
		cout << "twiddle " << endl;
		print(i+2, j+2);
		break;
	case 5:  // kill
		cout << "kill    " << endl;
		print(m+1, n+1);
		break;
	}
}

void solve() {
	// init
	cin >> x >> y;
	m = strlen(x)-1;
	n = strlen(y)-1;
	for (int ii = 0; ii < 6; ii++) cin >> cost[ii];
	memset(p, 0, sizeof(p));
	memset(mask, 0, sizeof(mask));
	memset(route, -1, sizeof(route));

	// process
	cout << "total_cost: " << dp(0, 0) << endl;
	print(0, 0);
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	LARGE_INTEGER _frequency, _start_time, _end_time;
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_start_time);
	#endif

	assert(sizeof(int) == 4);
	solve();
	
	#ifdef OFFLINE
	QueryPerformanceCounter(&_end_time);
	cout << endl << "The algorithm takes " << (_end_time.QuadPart-_start_time.QuadPart)*1000/_frequency.QuadPart << " ms to complete the run." << endl;
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
