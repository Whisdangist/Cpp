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

/* 双调欧几里得旅行商问题 p231 */

int V;
map<int, int> v;
vector<int> l;
double G[100][100], L[100][100];
bool mask[100][100];
int route[100][100];
vector<int> route2[2];

double dis(int i, int j) {
	if (i == j) return 0;
	if (G[i][j] != 0) {
		return G[i][j];
	}
	int x1 = l[i], x2 = l[j];
	G[i][j] = sqrt((x1-x2)*(x1-x2)+(v[x1]-v[x2])*(v[x1]-v[x2]));
	G[j][i] = G[i][j];
	return G[i][j];
}

double dp(int i, int j) {
	int tmp;
	if (mask[i][j]) {
		return L[i][j];
	}
	if (i > j) {
		swap(i, j);
	}
	ASSERT(i <= j);
	if (i == 0 && j == 1) {
		L[i][j] = dis(0, 1);
	}
	else if (i >= j-1) {
		for (int k = 0; k < i; k++) {
			double t = dp(i, k) + dis(k, j);
			if (t < L[i][j]) {
				L[i][j] = t;
				tmp = k;
			}
		}
	}
	else {
		L[i][j] = dp(i, j-1) + dis(j-1, j);
		tmp = j-1;
	}
	ASSERT(!IS_POS_INF(L[i][j]));
	route[i][j] = tmp;
	L[j][i] = L[i][j];
	mask[i][j] = true;
	mask[j][i] = true;
	return L[i][j];
}

void print(int i, int j) {
	if (i == 0 && j == 0) return;
	ASSERT(route[i][j] != -1);
	static int route_flag = 0;
	int prev = route[i][j];
	if (prev > i) {
		route2[route_flag].push_back(prev);
		print(i, prev);
	}
	else {
		route2[route_flag].push_back(prev);
		route_flag = !route_flag;
		print(prev, i);
	}
}

void solve() {
	// init
	cin >> V;
	int x, y;
	for (int i = 0; i < V; i++) {
		cin >> x >> y;
		v[x] = y;
		l.push_back(x);
	}
	sort(l.begin(), l.end());

	memset(route, -1, sizeof(route));
	memset(mask, 0, sizeof(mask));
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			L[i][j] = INF;
		}
	}

	// process
	ASSERT(v.size() >= 3);
	cout << "length: " << dp(V-1, V-1) << endl;
	print(V-1, V-1);
	cout << "line 1: ";
	for (auto i = route2[0].rbegin(); i != route2[0].rend(); i++) {
		cout << *i << " ";
	}
	cout << V-1 << endl;
	cout << "line 2: ";
	for (auto i = route2[1].rbegin(); i != route2[1].rend(); i++) {
		cout << *i << " ";
	}
	cout << V-1 << endl;
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
