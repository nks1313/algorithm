#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int T, N, M, answer;
int map[21][21];
bool visited[21][21];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
vector<pair<int, int>> home;
void init() {
	home.clear();
	answer = 0;
}

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) home.push_back({ i,j });
		}
	}
}

void solution() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int y = 1; y <= N; y++) for (int x = 1; x <= N; x++) visited[y][x] = false;
			int cnt = 0;
			queue<pair<int, int>> q;

			q.push({ i,j });
			visited[i][j] = true;

			int k = 0;
			while (!q.empty()) {
				k++;
				int sz = q.size();
				for (int m = 0; m < sz; m++) {
					int sy = q.front().first;
					int sx = q.front().second;
					q.pop();
					if (map[sy][sx] == 1) cnt++;

					for (int l = 0; l < 4; l++) {
						int ny = sy + dy[l];
						int nx = sx + dx[l];
						if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
						if (visited[ny][nx]) continue;

						q.push({ ny,nx });
						visited[ny][nx] = true;
					}
				}

				int p = cnt * M - (k * k + (k - 1) * (k - 1));

				if (p >= 0) answer = max(answer, cnt);
			}
		}
	}
}
void output(int tc) {
	cout << "#" << tc << " " << answer << "\n";
}
int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		input();
		solution();
		output(tc);
	}
}
