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

/* 字符串拆分问题 p234 */

int N, M;
int L[MAX_N];  // value from 1 to N-1
int cost[MAX_N][MAX_N];
bool mask[MAX_N][MAX_N];
int route[MAX_N][MAX_N];

int dp(int i, int j) {
	int l = L[i], r = L[j];
	if (i == j-1) return 0;
	if (mask[i][j]) return cost[i][j];
	int min = INF;
	for (int k = i+1; k < j; k++) {
		int t = dp(i, k) + dp(k, j) + r-l;
		if (t < min) {
			min = t;
			route[i][j] = k;
		}
	}
	mask[i][j] = true;
	cost[i][j] = min;
	return cost[i][j];
}

void print(int i, int j) {
	int k = route[i][j];
	if (k == -1) return;
	cout << k << " ";
	print(i, k);
	print(k, j);
}

void solve() {
	// init
	memset(cost, 0, sizeof(cost));
	memset(mask, 0, sizeof(mask));
	memset(route, -1, sizeof(route));
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> L[i];
	}
	L[0] = 0;
	L[M+1] = N;

	// process
	cout << "Minimum cost: " << dp(0, M+1) << endl;
	print(0, M+1);
	cout << endl;
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
