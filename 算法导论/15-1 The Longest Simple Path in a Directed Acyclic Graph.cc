#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))

/* 有向无环图中的最长简单路径问题 p231 */

int V, E;
int G[100][100], route[100][100];
bool mask[100][100];
vector<pair<int, int> > nxt[100];  // suppose V <= 100

// dynamic programming: top-down with memoization
int dp_td(int i, int j) {
	if (mask[i][j] == true) {
		return G[i][j];
	}
	for (auto k = nxt[i].begin(); k != nxt[i].end(); k++) {
		int t = k->second + dp_td(k->first, j);
		if (t >= G[i][j]) {
			G[i][j] = t;
			route[i][j] = k->first;
		}
	}
	mask[i][j] = true;
	return G[i][j];
}

void print(int i, int j) {
	if (i == j) {
		cout << i << " ";
		return;
	}
	ASSERT(route[i][j] != -1);
	cout << i << " ";
	print(route[i][j], j);
}

void solve() {
	// init
	memset(G, 0, sizeof(G));
	memset(mask, 0, sizeof(mask));
	memset(route, -1, sizeof(route));
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int from, to, edge;
		cin >> from >> to >> edge;
		G[from][to] = edge;
		nxt[from].push_back(make_pair(to, edge));
	}
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			G[i][j] = -INF;
			if (nxt[i].empty()) {
				mask[i][j] = true;
			}
		}
		G[i][i] = 0;
		mask[i][i] = true;
	}

	// process
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dp_td(i, j) == 0 || IS_NEG_INF(dp_td(i, j))) {
				continue;
			}
			cout << "length: " << dp_td(i, j) << "\t";
			cout << "route: ";
			print(i, j);
			cout << endl;
		}
	}
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	#endif

	assert(sizeof(int) == 4);
	solve();
	
	#ifdef OFFLINE
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
