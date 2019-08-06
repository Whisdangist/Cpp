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

/* 译码算法问题 p233 */

int tag[MAX_N][MAX_N];  // value from 1 to 10
double p[MAX_N][MAX_N];  // value from 0.01 to 0.99
double pp[MAX_N][MAX_N];
bool mask[MAX_N][MAX_N];
int route[MAX_N][MAX_N];
int s[MAX_N];
int V, E, K;

double dp(int v, int k) {
	if (k == K) return 1;
	if (mask[v][k]) return pp[v][k];
	map<int, double> nxt;
	for (int i = 0; i < V; i++) {
		if (tag[v][i] == s[k]) {
			nxt[i] = p[v][i] * dp(i, k+1);
		}
	}
	double max = 0;
	for (auto &n: nxt) {
		if (n.second > max) {
			max = n.second;
			route[v][k] = n.first;
		}
	}
	mask[v][k] = true;
	pp[v][k] = max;
	return pp[v][k];
}

void solve() {
	// init
	memset(tag, 0, sizeof(tag));
	memset(p, 0, sizeof(p));
	memset(pp, 0, sizeof(pp));
	memset(mask, 0, sizeof(mask));
	memset(route, -1, sizeof(route));
	cin >> V >> E >> K;
	for (int i = 0, x, y; i < E; i++) {
		cin >> x >> y;
		cin >> tag[x][y] >> p[x][y];
	}
	for (int i = 0; i < K; i++) {
		cin >> s[i];
	}
	

	// process
	cout << "possibility: " << dp(0, 0) << endl;
	for (int i = 0, v = 0; i < K; v = route[v][i++]) {
		cout << route[v][i] << " ";
	}
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
