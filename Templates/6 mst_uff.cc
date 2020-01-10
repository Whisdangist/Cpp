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
#define MAX_M 200000

int N, M;
struct Node {
	int parent;
	int rank;
} nodes[MAX_N+1];

int Find(int x) {
	if (nodes[x].parent == x) return x;
	return nodes[x].parent = Find(nodes[x].parent);
}

void Union(int x, int y) {
	int root_x = Find(x);
	int root_y = Find(y);
	if (root_x == root_y) return;
	if (nodes[root_x].rank > nodes[root_y].rank) {
		nodes[root_y].parent = root_x;
	}
	else if (nodes[root_x].rank < nodes[root_y].rank) {
		nodes[root_x].parent = root_y;
	}
	else {
		nodes[root_y].parent = root_x;
		nodes[root_x].rank++;
	}
}

struct Edge {
	int x, y;
	int weight;
	bool operator<(const Edge e) const {
		return this->weight < e.weight;
	}
} edges[MAX_M];

void solve() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		nodes[i].parent = i;
		nodes[i].rank = 0;
	}
	for (int i = 0; i < M; i++) {
		cin >> edges[i].x >> edges[i].y >> edges[i].weight;
	}

	sort(edges, edges+M);
	int sum = 0, cnt = 0;
	for (int i = 0; i < M; i++) {
		Edge e = edges[i];
		int root_x = Find(e.x);
		int root_y = Find(e.y);
		if (root_x == root_y) continue;
		Union(root_x, root_y);
		sum += e.weight; cnt++;
	}

	if (cnt < N-1) cout << "orz" << endl;
	else cout << sum << endl;
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
