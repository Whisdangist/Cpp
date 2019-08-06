#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp)
#endif

/* 最长公共子序列问题 p222 */

map<pair<string, string>, string> p;

// dynamic programming: top-down with memoization
string dp_td(string& s1, string& s2) {
	if (s1.size() == 0 || s2.size() == 0) {
		return string("");
	}
	pair<string, string> s1_s2 = make_pair(s1, s2);
	pair<string, string> s2_s1 = make_pair(s2, s1);
	if (p.find(s1_s2) != p.end()) {
		return p[s1_s2];
	}
	string tmp1 = s1.substr(0, s1.size()-1);
	string tmp2 = s2.substr(0, s2.size()-1);
	if (s1.back() == s2.back()) {
		string lcs = dp_td(tmp1, tmp2);
		lcs.append(1, s1.back());
		p[s1_s2] = lcs;
		p[s2_s1] = lcs;
		return lcs;
	}
	else {
		string lcs1 = dp_td(s1, tmp2);
		string lcs2 = dp_td(tmp1, s2);
		if (lcs1.size() > lcs2.size()) {
			p[s1_s2] = lcs1;
			p[s2_s1] = lcs1;
			return lcs1;
		}
		else {
			p[s1_s2] = lcs2;
			p[s2_s1] = lcs2;
			return lcs2;
		}
	}
}


void solve() {
	string str1, str2;
	cin >> str1 >> str2;
	cout << dp_td(str1, str2) << endl;
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	#endif

	solve();
	
	#ifdef OFFLINE
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
