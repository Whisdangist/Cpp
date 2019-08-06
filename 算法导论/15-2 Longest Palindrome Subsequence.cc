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

/* 最长回文子序列问题 p231 */

string dp(const string& s){
	if (s.size() <= 1) {
		return s;
	}
	if (s.front() == s.back()) {
		return s.front() + dp(s.substr(1, s.size()-2)) + s.back();
	}
	else {
		string res1 = dp(s.substr(0, s.size()-1));
		string res2 = dp(s.substr(1, s.size()-1));
		return res1.size() > res2.size() ? res1 : res2;
	}
}

void solve() {
	// init
	string str;
	cin >> str;

	// process
	cout << dp(str) << endl;
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
