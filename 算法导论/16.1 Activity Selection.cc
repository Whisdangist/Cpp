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

/* 活动选择问题 p237 */

int N;
struct A {
	int s, f;
} a[MAX_N];

vector<int> ga(const int i) {
	if (i >= N) return vector<int>();
	int nxt = N;
	for (int ii = i+1; ii < N; ii++) {
		if (a[ii].s >= a[i].f) {
			nxt = ii;
			break;
		}
	}
	vector<int> v = ga(nxt);
	v.push_back(i);
	return v;
}

void solve() {
	// init
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i].s;
	}
	for (int i = 0; i < N; i++) {
		cin >> a[i].f;
	}
	sort(a, a+N, [](A& a1, A& a2){ return a1.f < a2.f; });

	// process
	for (int a: ga(0)) {
		cout << a+1 << endl;
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
