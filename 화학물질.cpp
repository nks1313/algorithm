#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
int T, N, cnt, fir, ans;
int map[100][100];
int goFirst[100];
int goLast[100];
int DP[20][20];
vector<pair<int, int>> mats;
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1 ,0, 0 };

void init() {
	cnt = 0;
	mats.clear();
	for (int i = 0; i < 100; i++) {
		goFirst[i] = 0;
		goLast[i] = 0;
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			DP[i][j] = -1;
		}
	}
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
void makeMats() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!map[i][j]) continue;
			int width = 1, height = 1;

			queue<pair<int, int>> q;
			q.push({ i,j });
			map[i][j] = 0;
			while (!q.empty()) {
				int cy = q.front().first;
				int cx = q.front().second;
				q.pop();

				for (int k = 0; k < 4; k++) {
					int ny = cy + dy[k];
					int nx = cx + dx[k];
					if (ny < 0 || nx < 0 || ny >= N || nx >= N)
						continue;
					if (!map[ny][nx]) continue;

					map[ny][nx] = 0;
					q.push({ ny,nx });
					width = nx - j + 1;
					height = ny - i + 1;
				}
			}
			goFirst[width] = height;
			goLast[height] = width;
			fir = width;
		}
	}

	while (goFirst[fir]) {
		fir = goFirst[fir];
	}
	while (goLast[fir]) {
		mats.push_back({ fir,goLast[fir] });
		fir = goLast[fir];
	}
}
pair<int, pair<int, int>> DFS(int left, int right) {
	if (DP[left][right] != -1) return { DP[left][right], {mats[left].first,mats[right].second} };
	if (left == right) return{ DP[left][right] = 0, {mats[left].first,mats[right].second} };

	pair<int, pair<int, int>> ret1;
	pair<int, pair<int, int>> ret2;
	int ret = INT32_MAX;
	for (int i = left; i < right; i++) {
		ret1 = DFS(left, i);
		ret2 = DFS(i + 1, right);
		ret = min(ret, ret1.first + ret2.first + ret1.second.first * ret1.second.second * ret2.second.second);
	}

	DP[left][right] = ret;

	return { ret, {mats[left].first,mats[right].second} };
}
void solve() {
	makeMats();

	ans = DFS(0, mats.size() - 1).first;
}

void output(int tc) {
	cout << "#" << tc << " " << ans << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solve();
		output(tc);
	}
}