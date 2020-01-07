#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#pragma GCC optimize("O0")
#include <windows.h>
#define ASSERT(exp) assert(exp)
#else
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))


class LargeInt {
public:
	static const int digits = 4000;
	int nums[digits];

    LargeInt(string s) {
        memset(nums, 0, sizeof(nums));
        reverse(s.begin(), s.end());
        for (unsigned i = 0; i < s.size(); i++) {
            int num = s[i] - '0';
            if (num >= 0 && num <= 9) nums[i] = num;
        }
    }
	LargeInt(const unsigned long long &b) {
		unsigned long long t = b;
		for (int i = 0; i != digits; i++) {
			if (t != 0) {
				nums[i] = t % 10;
				t /= 10;
			}
			else {
				nums[i] = 0;
			}
		}
	}
	LargeInt& operator*=(const LargeInt &b) {
		LargeInt c = 0;
		for (int i = 0; i != digits; i++) {
			for (int j = 0; i+j < digits; j++) {
				c[i+j] += nums[i] * b[j];
			}
		}
		int flag = 0;
		for (int i = 0; i != digits; i++) {
			c[i] += flag;
			flag = c[i] / 10;
			nums[i] = c[i] % 10;
		}
		return *this;
	}
    LargeInt operator*(const LargeInt &b) const {
        LargeInt c = *this;
        c *= b;
        return c;
    }
	LargeInt& operator+=(const LargeInt &b) {
		int flag = 0;
		for (int i = 0; i != digits; i++) {
			nums[i] += b[i] + flag;
            flag = nums[i] / 10;
            nums[i] %= 10;
		}
		return *this;
	}
    LargeInt operator+(const LargeInt &b) const {
        LargeInt c = *this;
        c += b;
        return c;
    }
	LargeInt& operator-=(const LargeInt &b) {
		int flag = 0;
		for (int i = 0; i != digits; i++) {
			nums[i] -= b[i];
			nums[i] -= flag;
			if (nums[i] < 0) {
				nums[i] += 10;
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
		return *this;
	}
	const int& operator[](const int &index) const {
		return nums[index];
	}
	int& operator[](const int &index) {
		return nums[index];
	}

	LargeInt& pow(int b) {
		LargeInt a = *this;
		*this = 1;
		while (b) {
			if (b & 1) {
				*this *= a;
			}
			a *= a;
			b >>= 1;
		}
		return *this;
	}
	string to_string() {
		string str = "";
        bool zero_flag = false;
		for (int i = digits-1; i != -1; i--) {
            if (!zero_flag) { if (nums[i] == 0) continue; else zero_flag = true; }
			str += std::to_string((int)nums[i]);
		}
        if (str == "") str = "0";
		return str;
	}
};

void solve() {
	// init
	int P;
	cin >> P;
	LargeInt s = 2;
	s.pow(P);
	s -= 1;
	string str = s.to_string();

	// process
	cout << (int)(P * log10l(2) + 1) << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 50; j++) {
			cout << str[i*50+j];
		}
		cout << endl;
	}
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