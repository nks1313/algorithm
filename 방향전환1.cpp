#include <iostream>
#include <vector>
#include <utility>
#define MAXN 9
using namespace std;

int T, N, K, ans;
int map[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
void dfs(int y, int x, bool flag, int dist) {
	if (dist > ans) ans = dist;
	//cout << y << " " << x << " " << k << " " << dist << endl;
	for (int i = 0; i < 4; i++) {
		int nextY = y + dy[i];
		int nextX = x + dx[i];
		if (nextY < 1 || nextY > N || nextX < 1 || nextX > N)
			continue;
		if (visited[nextY][nextX]) continue;

		//���� ��尡 �� ���� ������ ���
		if (map[nextY][nextX] < map[y][x]) {
			visited[nextY][nextX] = true;
			dfs(nextY, nextX, flag, dist + 1);
			visited[nextY][nextX] = false;
		}
		else {
			//���� ��尡 ���ų� ���� �����ε�
			//���� Kĭ ���� �ʾҴٸ�
			if (!flag) {
				for (int k = 1; k <= K; k++) {
					if (map[nextY][nextX] - k < map[y][x]) {
						visited[nextY][nextX] = true;
						map[nextY][nextX] -= k;
						dfs(nextY, nextX, ~flag, dist + 1);
						map[nextY][nextX] += k;
						visited[nextY][nextX] = false;
					}
				}
			}
		}
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> K;

		ans = 0;
		int tmp = 0;
		vector<pair<int, int>> highst;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> map[i][j];
				if (map[i][j] > tmp) {
					tmp = map[i][j];
					highst.clear();
					highst.push_back({ i,j });
				}
				else if (map[i][j] == tmp) {
					highst.push_back({ i,j });
				}
			}
		}

		for (int i = 0; i < highst.size(); i++) {
			int y = highst[i].first;
			int x = highst[i].second;
			visited[y][x] = true;
			dfs(y, x, false, 1);
			visited[y][x] = false;
		}

		cout << "#" << tc << " " << ans << "\n";
	}

	system("pause");
}
