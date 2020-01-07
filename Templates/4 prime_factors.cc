#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#include <windows.h>
#define ASSERT(exp) assert(exp)
#else
#pragma GCC optimize(3)
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))

#define MAX_N 1000000

int N;
int prime_list[MAX_N/4];

int get_prime_list(int* list, int upper) {
	int num = 0;
	for (int i = 2; i < upper; i++) {
		bool flag = true;
		int sqrt_i = sqrt(i);
		for (int j = 0; j < num && list[j] <= sqrt_i; j++) {
			if (i % list[j] == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			list[num++] = i;
		}
	}
	return num;
}

int get_factors(int* prime_list, int* list, int num) {
	int factors_num = 0;
	for (int i = 0; num > 1; i++) {
		ASSERT(prime_list[i] <= num);
		if (num % prime_list[i] == 0) {
			list[factors_num++] = prime_list[i];
			while (num % prime_list[i] == 0) {
				num /= prime_list[i];
			}
		}
	}
	return factors_num;
}

void solve() {
	int prime_num = get_prime_list(prime_list, MAX_N);
	cout << "前1000个质数: " << endl;
	for (int i = 0; i < 1000; i++) cout << i << "\t" << prime_list[i] << endl;

	int factor_list[20];
	int factors_num = get_factors(prime_list, factor_list, 1000);
	cout << "\n1000的因数分解: " << endl;
	for (int i = 0; i < factors_num; i++) cout << factor_list[i] << endl;
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