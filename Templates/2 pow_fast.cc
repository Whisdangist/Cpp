// luogu-judger-enable-o2
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

typedef long long ll;

ll pow_fast(ll a, ll b) {
	ll s = 1;
	while (b > 0) {
		if (b & 1) {
			s *= a;
		}
		a *= a;
		b >>= 1;
	}
	return s;
}

ll pow_fast_mod(ll a, ll b, ll div) {
	ll s = 1;
	while (b > 0) {
		if (b & 1) {
			s %= div;
			a %= div;
			s *= a;
		}
		a %= div;
		a *= a;
		b >>= 1;
	}
	return s % div;
}

void solve() {
	ll a, b, div;
	cin >> a >> b >> div;
	cout << a << "^" << b << " mod " << div << "=" << pow_fast_mod(a, b, div) << endl;
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
	ios_base::sync_with_stdio(false);
	solve();
	
	#ifdef OFFLINE
	QueryPerformanceCounter(&_end_time);
	cout << endl << "The algorithm takes " << (_end_time.QuadPart-_start_time.QuadPart)*1000/_frequency.QuadPart << " ms to complete the run." << endl;
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}