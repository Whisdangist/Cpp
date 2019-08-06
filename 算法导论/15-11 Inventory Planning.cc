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

/* 库存规划问题 p235 */

int N, M, C;
int H(int j) { return j; }  // represent inventory costs
int d[MAX_N], p[MAX_N][MAX_N];


int dp(int n, int m) {
	if (p[n][m] != -1) return p[n][m];
	if (n == 0) {
		p[n][m] = (d[n]+m <= M) ? H(M-d[n]-m) : (d[n]+m-M)*C;
		return p[n][m];
	}
	int min = INF;
	for (int i = 0; i <= M; i++) {
		int cost = (d[n]+m <= M+i) ? H(M+i-d[n]-m) : (d[n]+m-M-i)*C;
		int t = dp(n-1, i) + cost;
		if (t < min) {
			min = t;
		}
	}
	p[n][m] = min;
	return p[n][m];
}

void solve() {
	// init
	memset(p, -1, sizeof(p));
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++) {
		cin >> d[i];
	}
	// process
	cout << "Minimum costs: " << dp(N-1, 0) << endl;
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	ios_base::sync_with_stdio(false);
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
