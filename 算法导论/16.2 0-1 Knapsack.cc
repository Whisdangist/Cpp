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

/* 0-1 背包问题 p243 */

int N, W;
int v[MAX_N], w[MAX_N];
int dp[MAX_N][MAX_N];
int dp1[MAX_N];

void solve() {
	// init
	cin >> N >> W;
	for (int i = 1; i <= N; i++) {
		cin >> w[i] >> v[i];
	}

	// dp
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= W; j++) {
			dp[i][j] = dp[i-1][j];
			if (j >= w[i]) {
				int t = dp[i-1][j-w[i]] + v[i];
				if (t > dp[i][j]) {
					dp[i][j] = t;
				}
			}
		}
	}

	// dp1
	for (int i = 1; i <= N; i++) {
		for (int j = W; j >= w[i]; j--) {
			dp1[j] = max(dp1[j], dp1[j-w[i]] + v[i]);
		}
	}

	// process
	cout << "Maximum value: " << dp[N][W] << endl;
	cout << "Maximum value: " << dp1[W] << endl;
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
