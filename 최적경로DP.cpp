#include <iostream>
#include <algorithm>
using namespace std;
int T, N, ans;
int c[12][2];
int dist[12][12];
int DP[11][(1 << 11)];
int dfs(int depth, int node, int visited) {
	if (depth == N){
		return dist[node][N + 1];
	}

	if(DP[node][visited] > 0){
		return DP[node][visited];
	}
	 
	int ret = 0x7fffffff;
	for (int i = 1; i <= N; i++) {
		if (visited & (1 << i)) continue;
		ret = min(ret, dfs(depth + 1, i, visited | (1 << i)) + dist[node][i]);
	}

	return DP[node][visited] = ret;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j < (1 << 11); j++) {
				DP[i][j] = 0;
			}
		}

		cin >> N;
		cin >> c[0][0] >> c[0][1] >> c[N+1][0] >> c[N + 1][1];
		for (int i = 1; i < N + 1; i++) {
			cin >> c[i][0] >> c[i][1];
		}

		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				dist[i][j] = abs(c[i][0] - c[j][0]) + abs(c[i][1] - c[j][1]);
				dist[j][i] = dist[i][j];
			}
		}

		dfs(0, 0, 0);

		cout << "#" << tc << " " << DP[0][0] << "\n";
	}
}