#include <iostream>
#include <algorithm>
#define MOD 1000000000

using namespace std;
long long DP[201][201];
int N, K;

long long solve(int depth, long long sum) {
	if (DP[depth][sum] > 0) return DP[depth][sum];
	if (depth == K-1) return 1;
	if (sum == N) return 1;

	long long ret = 0;
	for (int i = 0; i <= N - sum; i++) {
		ret += solve(depth + 1, sum + i);
		ret %= MOD;
	}

	return DP[depth][sum] = ret;
}
int main() {
	cin >> N >> K;
	cout << solve(0, 0)%MOD;
}