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

#define MAX_N 1000

/* 整齐打印问题 p232 */

int N, M;
string word[MAX_N];  // suppose N <= MAX_N
int extra[MAX_N][MAX_N], value[MAX_N][MAX_N], route[MAX_N][MAX_N];

inline int cubic(int x) {
	return pow(x, 3);
}

int ext(int i, int j) {
	if (extra[i][j] != -1) {
		return extra[i][j];
	}
	ASSERT(M > 0 && M < 1000);
	int t = M - j + i;
	for (int k = i; k <= j; k++) {
		t -= word[k].size();
		if (t < 0) {
			for (int jj = j; jj < N; jj++) {
				extra[i][jj] = -2;
			}
			return -2;
		}
	}
	extra[i][j] = t;
	return extra[i][j];	
}

int dp(int i, int j) {
	if (value[i][j] != -1) {
		return value[i][j];
	}
	if (ext(i, j) > 0) {
		value[i][j] = cubic(ext(i, j));
		route[i][j] = -2;
		return value[i][j];
	}
	int min = INF;
	for (int k = i+1; k < j; k++) {
		int t = dp(i, k) + dp(k+1, j);
		if (t < min) {
			min = t;
			route[i][j] = k;
		}
	}
	value[i][j] = min;
	return value[i][j];
}

void print(int i, int j) {
	int k = route[i][j];
	ASSERT(k != -1);
	if (k == -2) {
		cout << "|";
		for (int m = i; m <= j; m++) {
			cout << word[m] << " ";
		}
		string spaces(ext(i, j), ' ');
		cout << spaces << "|" << endl;
	}
	else {
		print(i, k);
		print(k+1, j);
	}
}

void solve() {
	// init
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> word[i];
	}
	memset(extra, -1, sizeof(extra));
	memset(value, -1, sizeof(value));
	memset(route, -1, sizeof(route));

	// process
	int first = 0;
	for (int i = N-1; i >= 0 && ext(i, N-1) > 0; i--) {
		first = i;
	}
	int res = INF, end = 0;
	for (int i = first-1; i < N; i++) {
		if (dp(0, i) < res) {
			res = dp(0, i);
			end = i;
		}
	}
	ASSERT(end != 0);	
	cout << "algorithms output value: " << res << endl;
	print(0, end);
	if (end != N-1) {
		cout << "|";
		for (int i = end+1; i < N; i++) {
			cout << word[i] << " ";
		}
		string spaces(ext(end+1, N-1), ' ');
		cout << spaces << "|" << endl;
	}

	int res1 = 0, end1 = 0;
	vector<string> lines;
	for (int i = 0, j = 0; j < N; j++) {
		if (ext(i, j) > 0) continue;
		// ext(i, j) < 0
		j--;
		string line("|");
		for (int k = i; k <= j; k++) {
			line.append(word[k]).append(" ");
		}
		string spaces(ext(i, j), ' ');
		line.append(spaces).append("|");
		lines.push_back(line);
		res1 += cubic(ext(i, j));
		i = j+1;
		end1 = j;
	}
	if (end1 != N-1) {
		string line("|");
		for (int i = end1+1; i < N; i++) {
			line.append(word[i]).append(" ");
		}
		string spaces(ext(end1+1, N-1), ' ');
		line.append(spaces).append("|");
		lines.push_back(line);
	}
	cout << endl << "non-algorithms output value: " << res1 << endl;
	for (auto l = lines.begin(); l != lines.end(); l++) {
		cout << *l << endl;
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
