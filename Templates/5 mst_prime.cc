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

typedef long long ll;

#define MAX_N 5000
#define MAX_M 

int N;
int pos[MAX_N+1][2];
struct Node {
	int index;
	long double key = INF;
	bool operator<(const Node n) const {
		return this->key < n.key;
	}
};

template <typename T>
struct Heap {
	int size = 0;
	T a[MAX_N+1];
	void heapify(int index) {
		int left = index * 2;
		int right = index * 2 + 1;
		int smallest = index;
		if (left <= size) {
			smallest = a[left] < a[right] ? left : right;
		}
		if (right <= size) { 
			smallest = a[smallest] < a[index] ? smallest : index;
		}
		if (smallest != index) {
			T temp = a[smallest];
			a[smallest] = a[index];
			a[index] = temp;
			heapify(smallest);
		}
	}
	void decrease_key(int index) {
		int parent = index / 2;
		if (parent > 0) {
			if (a[index] < a[parent]) {
				T temp = a[parent];
				a[parent] = a[index];
				a[index] = temp;
				decrease_key(parent);
			}
		}
	}
	void sort() {
		while (size > 1) {
			T temp = a[1];
			a[1] = a[size];
			a[size--] = temp;
			heapify(1);
		}
	}
	void push(T n) {
		a[++size] = n;
		decrease_key(size);
	}
	void pop() {
		a[1] = a[size--];
		heapify(1);
	}
	T top() {
		return a[1];
	}
};

Heap<Node> q;

inline long double distance(int i, int j) {
	return sqrtl(powl(pos[i][0]-pos[j][0], 2) + powl(pos[i][1]-pos[j][1], 2));
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> pos[i][0] >> pos[i][1];
	}

	for (int i = 1; i <= N; i++) {
		Node n;
		n.key = i > 1 ? INF : 0;
		n.index = i;
		q.push(n);
	}

	long double sum = 0;
	while (q.size > 0) {
		Node v = q.top();
		q.pop();
		sum += v.key;
		for (int i = 1; i <= q.size; i++) {
			if (q.a[i].key > distance(v.index, q.a[i].index)) {
				q.a[i].key = distance(v.index, q.a[i].index);
				q.decrease_key(i);
			}
		}
	}

	printf("%.2Lf\n", sum);
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
