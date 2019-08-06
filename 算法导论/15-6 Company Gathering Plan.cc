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

/* 公司聚会计划问题 p233 */

struct Staff {
	Staff *parent;
	Staff *left_child, *right_sibling;
	string name;
	double score;
	double scores[2];
	bool isCome[2];
};

int N;
Staff staff[MAX_N];
vector<Staff*> staff_list;

double dp(Staff* s, bool isLeaderCome) {
	if (s == nullptr) return 0;
	if (s->scores[isLeaderCome] != -1) return s->scores[isLeaderCome];
	if (isLeaderCome == false) {
		double t0 = dp(s->left_child, false);
		double t1 = dp(s->left_child, true) + s->score;
		if (t0 > t1) {
			s->scores[isLeaderCome] = t0 + dp(s->right_sibling, false);
		}
		else {
			s->isCome[isLeaderCome] = true;
			s->scores[isLeaderCome] = t1 + dp(s->right_sibling, false);
		}
	}
	else {
		s->scores[isLeaderCome] =  dp(s->left_child, false) + dp(s->right_sibling, true);
	}
	return s->scores[isLeaderCome];
}

void print(Staff* s, bool isLeaderCome) {
	if (s == nullptr) return;
	if (s->isCome[isLeaderCome] == true) {
		staff_list.push_back(s);
	}
	print(s->left_child, s->isCome[isLeaderCome]);
	print(s->right_sibling, isLeaderCome);
}

void solve() {
	// init
	cin >> N;
	for (int i = 0; i < N; i++) {
		int left, right;
		cin >> staff[i].name >> staff[i].score >> left >> right;
		if (left == -1) {
			staff[i].left_child = nullptr;
		}
		else {
			staff[i].left_child = staff + left;
		}
		if (right == -1) {
			staff[i].right_sibling = nullptr;
		}
		else {
			staff[i].right_sibling = staff + right;
		}
		staff[i].scores[0] = -1;
		staff[i].scores[1] = -1;
		staff[i].isCome[0] = false;
		staff[i].isCome[1] = false;
	}
	// staff[0].parent = nullptr;
	// for (int i = 0; i < N; i++) {
	// 	for (Staff *child = staff[i].left_child; child != nullptr; child = child->right_sibling) {
	// 		child->parent = staff + i;
	// 	}
	// }
	
	// process
	cout << "total_score: " << dp(staff + 1, false) << endl;
	print(staff + 1, false);
	// sort(staff_list.begin(), staff_list.end());
	// double sum = 0;
	for (auto s : staff_list) {
		// ASSERT(find(staff_list.begin(), staff_list.end(), s->parent) == staff_list.end());
		// sum += s->score;
		cout << s-staff << "\t" << s->score << "\t" << s->name << endl;
	}
	// ASSERT(fabs(sum - dp(staff + 1, false)) < 1e-2);
}

int main() {
	#ifdef OFFLINE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	ios_base::sync_with_stdio(false);
	LARGE_INTEGER _frequency, _start_time, _end_time;
	QueryPerformanceFrequency(&_frequency);
	QueryPerformanceCounter(&_start_time);
	#endif

	assert(sizeof(int) == 4);
	solve();
	
	#ifdef OFFLINE
	QueryPerformanceCounter(&_end_time);
	cout << endl << "The algorithm takes " << (_end_time.QuadPart-_start_time.QuadPart)*1000/_frequency.QuadPart << " ms to complete the run." << endl;
	freopen("CON", "r", stdin);
	system("pause");
	#endif
	return 0;
}
