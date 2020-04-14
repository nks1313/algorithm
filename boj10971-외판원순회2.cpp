#include <iostream>
#include <algorithm>
using namespace std;
int N, ans = INT32_MAX;
int w[11][11];

void dfs(int depth, int node, int sum, int visited) {
	if (sum > ans) return;

	if (depth == N) {
		if (w[node][1] == 0) return;

		int temp = sum + w[node][1];
		if (ans > temp) ans = temp;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (visited & (1 << i)) continue;
		if (w[node][i] == 0) continue;
		dfs(depth + 1, i, sum + w[node][i], visited | (1 << i));
	}
}
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> w[i][j];
		}
	}

	dfs(1, 1, 0, 1<<1);

	cout << ans;
}