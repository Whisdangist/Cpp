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

template <typename T>
inline void _merge(T *first1, T *last1, T *first2, T *last2, T *result, bool (*comp)(T&, T&) = [](T &a, T &b){ return a <= b; }) {
	int size = last1-first1+last2-first2;
	T* tmp = new T[size];
	T *i = first1, *j = first2;
	int k = 0;
	while (true) {
		if (comp(*i, *j)) {
			tmp[k++] = *i++;
			if (i == last1) break;
		}
		else {
			tmp[k++] = *j++;
			if (j == last2) break;
		}
	}
	if (i < last1) {
		for (T *ii = last1-1, *kk = result+size-1; ii >= i;) {
			*kk-- = *ii--;
		}
	}
	else if (last2 != result + size) {
		for (T *jj = last2-1, *kk = result+size-1; jj >= j;) {
			*kk-- = *jj--;
		}
	}
	T *kk = result;
	for (int ii = 0; ii < k;) {
		*kk++ = tmp[ii++];
	}
	delete[] tmp;
}

template <typename T>
void merge_sort(T *p, T *r, bool (*comp)(T&, T&) = [](T &a, T &b){ return a <= b; }) {
	ASSERT(p < r);
	if (p < r-1) {
		T *q = (int)((r-p)/2) + p;
		merge_sort(p, q, comp);
		merge_sort(q, r, comp);
		_merge(p, q, q, r, p, comp);
	}
}

int *a;
void solve() {
	int N;
	cin >> N;
	a = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	// sort(a, a+N);
	merge_sort<int>(a, a+N);
	for (int i = 0; i < N-1; i++) {
		cout << a[i] << " ";
	}
	cout << a[N-1] << endl;

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
