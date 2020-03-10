#include <iostream>
#include <algorithm>
using namespace std;
int T, N, ans;
int c[12][2];
int dist[12][12];
bool visited[12];
void dfs(int depth, int node, int sum) {
	if (depth == N) {
		cout << sum << endl;
		if (sum + dist[node][1] < ans) ans = sum + dist[node][1];
		return;
	}

	if (sum > ans) return;

	for (int i = 2; i < N + 2; i++) {
		if (visited[i]) continue;
		visited[i] = true;
		dfs(depth + 1, i,sum + dist[node][i]);
		visited[i] = false;
	}
}
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = INT32_MAX;
		cin >> N;
		for (int i = 0; i < N + 2; i++) {
			cin >> c[i][0] >> c[i][1];
		}
		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				dist[i][j] = abs(c[i][0] - c[j][0]) + abs(c[i][1] - c[j][1]);
				dist[j][i] = dist[i][j];
			//	cout << dist[i][j] << endl;
			}
		}

		for (int i = 2; i < N + 2; i++) {
			visited[i] = true;
			dfs(0, i,dist[0][i]);
			visited[i] = false;
		}

		cout << "#" << tc << " " << ans << "\n";
	}
}