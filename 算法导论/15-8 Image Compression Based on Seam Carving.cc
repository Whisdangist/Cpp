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

/* 基于裁剪的图像压缩问题 p234 */

int M, N;
double d[MAX_N][MAX_N];
double ds[MAX_N][MAX_N];
bool mask[MAX_N][MAX_N];
int route[MAX_N][MAX_N];

double dp(int i, int j) {
	if (i == M-1) return d[i][j];
	if (mask[i][j]) return ds[i][j];
	double t[3];
	t[0] = j == 0 ? INF : d[i][j] + dp(i-1, j);
	t[1] = d[i][j] + dp(i, j);
	t[2] = j == N-1 ? INF : d[i][j] + dp(i+1, j);
	double min = INF;
	for (int ii = 0; ii < 3; ii++) {
		if (t[ii] < min) {
			min = t[ii];
			route[i][j] = ii;
		}
	}
	ASSERT(min > 0 && !IS_POS_INF(min));
	mask[i][j] = true;
	ds[i][j] = min;
	return ds[i][j];
}

void print(int i, int j) {
	if (i == M) return;
	cout << i << "\t" << j << endl;
	ASSERT(route[i][j] != -1);
	print(i+1, j+route[i][j]-1);
}

void solve() {
	// init
	memset(route, 0, sizeof(route));
	memset(mask, 0, sizeof(mask));
	memset(ds, 0, sizeof(ds));
	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> d[i][j];
		}
	}

	// process
	double min = INF;
	int index = -1;
	for (int i = 0; i < N; i++) {
		if (dp(0, i) < min) {
			min = dp(0, i);
			index = i;
		}
	}
	cout << "Minimun damage degree: " << min << endl;
	ASSERT(index != -1);
	print(0, index);
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
