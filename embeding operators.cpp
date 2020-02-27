#include <stdio.h>
#define MAXN 12
#define MAXOPER 4
int T, N, maxAns, minAns;
int ops[MAXOPER];
int nums[MAXN];
int perm[MAXN - 1];
int calc(int opCnt, int depth ,int sum) {
	if (opCnt == 0) { sum += nums[depth + 1]; }
	else if (opCnt == 1) { sum -= nums[depth + 1]; }
	else if (opCnt == 2) { sum *= nums[depth + 1]; }
	else { sum /= nums[depth + 1]; }
	return sum;
}
void solve(int depth, int sum) {
	if (depth == N - 1) {
		int sum = nums[0];
		for (int numCnt = 1; numCnt < N ; numCnt++) {
			
		}
		maxAns = (maxAns > sum) ? maxAns : sum;
		minAns = (minAns < sum) ? minAns : sum;
		return;
	}

	for (int opCnt = 0; opCnt < 4; opCnt++) {
		if (ops[opCnt] > 0) {
			ops[opCnt]--;
			solve(depth + 1 , calc(opCnt, depth, sum));
			ops[opCnt]++;
		}
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		minAns = 100000000; maxAns = minAns * (-1);
		scanf("%d", &N);
		for (int i = 0; i < 4 ;i++)scanf("%d", &ops[i]);
		for (int i = 0; i < N; i++)scanf("%d", &nums[i]);

		solve(0 , nums[0]);

		printf("#%d %d", tc, maxAns - minAns);
	}

	return 0;
}