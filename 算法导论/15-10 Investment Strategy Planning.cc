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

/* 投资策略规划问题 p234 */

const int M = 10;
int N, F1, F2;
double D = 10000;
double r[MAX_N][M];
double p[M], route[M];

double dp(int m) {
	if (p[m] != -1) return p[m];
	if (m == -1) return D;
	double max = -1;
	for (int i = 0; i < N; i++) {
		double t = dp(m-1)*r[i][m];
		if (m > 0) t -= route[m-1] == i ? F1 : F2;
		if (t > max) {
			max = t;
			route[m] = i;
		}
	}
	ASSERT(max != -1);
	p[m] = max;
	return p[m];
}

void solve() {
	// init
	memset(p, -1, sizeof(p));
	memset(route, -1, sizeof(route));
	cin >> N >> F1 >> F2;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> r[i][j];
		}
	}

	// process
	cout << "Maximum imcome: " << dp(M) << endl;
	for (int i = 0; i < M; i++) {
		cout << "Year" << i+1 << "'s choice: " << route[i] << endl;
	}
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
