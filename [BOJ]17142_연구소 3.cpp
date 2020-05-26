#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int N, M, answer;
int map[50][50];
vector<pair<int, int>> virus;
pair<int, int> selected[10];
bool visited[50][50];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void spread() {
	int ret = 0;
	queue<pair<int, int>> q;
	for (int i = 0; i < M; i++) {
		q.push(selected[i]);
		visited[selected[i].first][selected[i].second];
	}

	int t = -1;
	while (!q.empty()) {
		t++;
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			//���� ��� ó��
			if (map[y][x] != 2) {
				ret = t;
			}

			//���� ��� ó��
			for (int j = 0; j < 4; j++) {
				int ny = y + dy[j];
				int nx = x + dx[j];

				if (ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx] && map[ny][nx] != 1) {
					q.push({ ny,nx });
					visited[ny][nx] = true;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j] == 0) {
				return;
			}
		}
	}

	answer = min(answer, ret);
}

void select(int depth, int num) {
	if (depth == M) {
		memset(visited, false, sizeof(visited));
		spread();
		return;
	}

	for (int i = num; i < virus.size(); i++) {
		selected[depth] = virus[i];
		select(depth + 1, i + 1);
	}
}

int main() {
	answer = 0x7fffffff;
	//�Է�
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) virus.push_back({ i,j });
		}


	//M���� �̴´�.
	select(0, 0);

	if (answer == 0x7fffffff) cout << -1;
	else cout << answer;
}