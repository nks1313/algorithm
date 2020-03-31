#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int DP[100001];
int N;


int solve(int n) {
	if (DP[n] > 0) return DP[n];
	int i = sqrt(n);
	if (n == i * i) return 1;


	int ret = 100000;
	for (; i > 0; i--) {
		ret = min(ret, solve(n - i * i) + 1);
	}

	return DP[n] = ret;
}

int main() {
	cin >> N;
	cout << solve(N) << "\n";
}